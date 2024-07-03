
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
#include "safe.h"
#include "log.h"

void *il2cpp_handle = nullptr;
uint64_t il2cpp_base = 0;
Cheat cheat[8];


uint64_t get_module_base(const char *name) {
    uint64_t addr = 0;
    char line[1024];
    uint64_t end = 0;
    char flags[5];
    char path[PATH_MAX];

    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp) {
        return addr;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (!strstr(line, name)) {
            continue;
        }

        strcpy(path, "");
        sscanf(line, "%" PRIx64"-%" PRIx64" %s %*" PRIx64" %*x:%*x %*u %s\n", &addr, &end,
               flags, path);

        if (memcmp((void *) addr, ELFMAG, SELFMAG) == 0) {
            break;
        } else {
            addr = 0;
        }
    }
    fclose(fp);

    return addr;
}


void patch_method(uint64_t base) {
    LOGI("il2cpp_base = %lx", il2cpp_base);
    il2cpp_handle = xdl_open("libil2cpp.so", 0);
    LOGI("il2cpp_handle = %p", il2cpp_handle);

    sleep(5);

//    find or set the cheat offset
    cheat[0].offset = 0x12345678;
    cheat[0].found = true;
}

void hack_thread() {
    LOGI("api: %d", api_level());

    for (int i = 0; i < 5; ++i) {
        sleep(1);
        il2cpp_base = get_module_base("libil2cpp.so");
        if (il2cpp_base > 0x8000) {
            patch_method(il2cpp_base);
            return;
        }
    }

    LOGE("failed to find il2cpp in %d", getpid());
}
