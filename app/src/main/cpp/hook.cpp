
#include <link.h>
#include <cinttypes>
#include <cstring>
#include <dlfcn.h>
#include <pthread.h>
#include <sys/system_properties.h>
#include <unistd.h>

#include <xdl.h>
#include <dobby.h>
#include "hook.h"
#include "log.h"

#include "il2cpp/il2cpp-tabledefs.h"
#include "il2cpp/il2cpp-class.h"


#define DO_API(r, n, p) r (*n) p

#include "il2cpp/il2cpp-api-functions.h"

#undef DO_API

uint64_t il2cpp_base = 0;
Cheat cheat[8];


void init_il2cpp_api(void *handle) {
#define DO_API(r, n, p) {                      \
    n = (r (*) p)xdl_sym(handle, #n, nullptr); \
    if(!n) {                                   \
        LOGW("api not found %s", #n);          \
    }                                          \
}
#include "il2cpp/il2cpp-api-functions.h"

#undef DO_API
}


int api_level() {
    char value[92] = {0};
    if (__system_property_get("ro.build.version.sdk", value) < 1) return -1;
    int api_level = (int) strtol(value, nullptr, 10);
    return (api_level > 0) ? api_level : -1;
}


void analyze_image(const Il2CppImage* image, const char* _namespace,
                   const char* class_name, const char* method_name,
                   int param_count, int index) {
    auto klass = il2cpp_class_from_name(image, _namespace, class_name);
    if (!klass) {
        LOGE("[klass] can't found [%s] in [%s]", class_name, _namespace);
        return;
    }
    auto method = il2cpp_class_get_method_from_name(klass, method_name, param_count);
    if (method) {
        LOGE("[method] can't found [%s] in [%s]", method_name, class_name);
        return;
    }
    cheat[index].found = true;
    cheat[index].offset = (uint64_t) method->methodPointer - il2cpp_base;
    LOGI("cheat[%d].offset: %p", index, (void*) cheat[index].offset);
}

// Automatically search for the cheat method offset
void search_offset(void* handle) {
    LOGI("il2cpp_handle: %p", handle);
    init_il2cpp_api(handle);
    if (il2cpp_domain_get_assemblies) {
        Dl_info dlInfo;
        if (dladdr((void *) il2cpp_domain_get_assemblies, &dlInfo)) {
            il2cpp_base = reinterpret_cast<uint64_t>(dlInfo.dli_fbase);
        }
        LOGI("il2cpp_base: %" PRIx64"", il2cpp_base);
    } else {
        LOGE("Failed to initialize il2cpp api, my github has written about solutions.");
        return;
    }

    if (!il2cpp_assembly_get_image) {
        LOGE("il2cpp_assembly_get_image is null, my github has written about solutions.");
        return;
    }

    while (!il2cpp_is_vm_thread(nullptr)) {
        LOGI("Waiting for il2cpp_init...");
        sleep(1);
    }

    size_t size;
    auto domain = il2cpp_domain_get();
    auto il2cpp_thread = il2cpp_thread_attach(domain);
    auto assemblies = il2cpp_domain_get_assemblies(domain, &size);

    for (int i = 0; i < size; ++i) {
        auto image = il2cpp_assembly_get_image(assemblies[i]);
        auto image_name = il2cpp_image_get_name(image);
        if (strcmp(image_name, "Assembly-CSharp.dll") != 0) {
            continue;
        }

        // Search for examples

        // NameSpace: ns_aaa
        // class: clz_eg1
        // public boolean finish() ;
        analyze_image(image, "ns_aaa", "clz_aaa", "finish", 0, 0);

        // NameSpace: ns_ddd
        // class: clz_ddd
        // public single getSPRate(single ratio) ;
        analyze_image(image, "ns_ddd", "clz_ddd", "getSPRate", 1, 3);

        break;
    }

    il2cpp_thread_detach(il2cpp_thread);
}


void hack_thread() {
    LOGI("api: %d", api_level());

    for (int i = 0; i < 10; ++i) {
        sleep(1);
        void* handle = xdl_open("libil2cpp.so", 0);
        if (handle) {
            search_offset(handle);
            return;
        }
    }

    LOGE("Failed to find il2cpp in %d", getpid());
}
