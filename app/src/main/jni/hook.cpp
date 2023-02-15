
#include <link.h>               //dl_iterate_phdr
#include <cinttypes>
#include <cstring>
#include <dlfcn.h>              //Dl_info
#include <pthread.h>            //pthread_create
#include <sys/system_properties.h>      //PROP_VALUE_MAX
#include <unistd.h>
#include <sys/inotify.h>        //inotify

#include <xdl.h>
#include <dobby.h>
#include "hook.h"
#include "obfuscate.h"

void* il2cpp_handle = nullptr;
uint64_t il2cpp_base = 0;
Cheat cheat[8];

const char *get_prop(const char *prop) {
    static char prop_value[PROP_VALUE_MAX];
    memset(prop_value, 0, sizeof(prop_value));
    __system_property_get(prop, prop_value);

    return prop_value;
}

unsigned long get_module_base(const char* name) {
    unsigned long start = 0;
    unsigned long end = 0;
    unsigned long ptr = 10;
    char flags[5];
    char line[1024] = {};
    char path[1024] = {};

    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp)
        return 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, name)) {
            int num = sscanf(line, "%lx-%lx %s %lx %*x:%*x %*u %s\n",
                             &start, &end, flags, &ptr, path);
            if (num != 5)   continue;
            if (ptr == 0 && !strstr(line, "-s")) {
                break;
            }
        }
    }
    fclose(fp);

    return start;
}

void *hack_thread(void *) {
    const int api_level = atoi(get_prop("ro.build.version.sdk"));
    LOGI("api: %d", api_level)

    for (int i = 0; i < 5; ++i) {
        sleep(1);
        il2cpp_base = get_module_base("libil2cpp.so");
        if (il2cpp_base > 0x8000) {
            //LOGI("il2cpp_base = %lx", il2cpp_base)
            il2cpp_handle = xdl_open("libil2cpp.so", 0);

            sleep(5);
            // To find cheat offset
//            cheat[0].offset = 0x12345678;
//            cheat[0].found = true;
            return nullptr;
        }
    }

    LOGE("libil2cpp.so not found in %d", getpid())
    return il2cpp_handle;
}


HOOK_DEF(int, openat, int fd, const char *path, int flag, int mode) {
    if (strlen(path) > 20 && strstr(path, ".apk")) {
        LOGI(obf("[openat] fd = %d path = %s flag = %d mode = %d"), fd, path, flag, mode)
        //return orig_openat(fd, fake_path, flag, mode);
    }

    return orig_openat(fd, path, flag, mode);
}

static void* thread_hook_openat(void*) {
    void *handle = xdl_open("libc.so", XDL_DEFAULT);
    if (handle) {
        void *symbol = xdl_dsym(handle, "__openat", nullptr);
        int result = DobbyHook(symbol, (dobby_dummy_func_t) new_openat,
                               (dobby_dummy_func_t *) &orig_openat);
        LOGI(obf("hook_openat result = %d"), result)
    }
    return nullptr;
}

/**线程监视 /proc/self/mem */
static void* thread_inotify(void*) {
    int fd = inotify_init();
    if (fd < 0) {
        //crashAPP();
        return il2cpp_handle;
    }

    char memPath[32] = {};
    char mapPath[32] = {};
    sprintf(memPath, "/proc/%d/mem", getpid());
    sprintf(mapPath, "/proc/%d/pagemap", getpid());

    int mem = inotify_add_watch(fd, memPath, IN_ALL_EVENTS);
    int map = inotify_add_watch(fd, mapPath, IN_ALL_EVENTS);
    if (mem < 0 || map < 0) {
        return il2cpp_handle;
    }

    const int buf_len = sizeof(struct inotify_event) * 0x100;
    char buf[buf_len] = {0};
    fd_set readfds;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        int iRet = select(fd + 1, &readfds, nullptr,
                          nullptr, nullptr); // 此处阻塞
        if (-1 == iRet)
            break;

        if (iRet) {
            memset(buf, 0, buf_len);
            ssize_t len = read(fd, buf, buf_len);

            unsigned long i = 0;

            while (i < len) {
                auto *event = (struct inotify_event *) &buf[i];
                //(event->mask & IN_ACCESS) || (event->mask & IN_CLOSE)  IN_OPEN
                if ((event->mask & IN_ACCESS)) {
                    // crashAPP();
                    // exit(-1);
                    //__asm __volatile(".int 0x8c89fa98");
                }
                i += sizeof(struct inotify_event) + event->len;
            }
        }
    }

    inotify_rm_watch(fd, map);
    inotify_rm_watch(fd, mem);
    close(fd);

    return nullptr;
}
