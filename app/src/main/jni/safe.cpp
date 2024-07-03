
#include <sys/wait.h>
#include <dobby.h>
#include <elf.h>
#include <climits>
#include <cinttypes>
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <linux/in.h>
#include <random>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <thread>
#include <vector>

#include <cstdlib>
#include <cstring>

#include <fcntl.h>
#include "safe.h"
#include "log.h"

bool maps_changeA = true;

int openat_2(const char *path, int flag) {
    return (int) syscall(__NR_openat, AT_FDCWD, path, flag, 600);
}

/**按行读取文本内容*/
ssize_t read_one_line(int fd, char *buf, size_t len) {
    char b;
    ssize_t ret;
    ssize_t bytes_read = 0;

    memset(buf, 0, len);

    do {
        ret = read(fd, &b, 1);

        if (ret != 1) {
            if (bytes_read == 0) {
                // error or EOF
                return -1;
            } else {
                return bytes_read;
            }
        }

        if (b == '\n') {
            return bytes_read;
        }

        *(buf++) = b;
        bytes_read += 1;

    } while (bytes_read < len - 1);

    return bytes_read;
}


int api_level() {
    char value[92] = {0};
    if (__system_property_get("ro.build.version.sdk", value) < 1) return -1;
    int api_level = (int) strtol(value, nullptr, 10);
    return (api_level > 0) ? api_level : -1;
}


class safeInfo {
public:
    class soinfo {
    public:
        uint64_t base = 0;
        uint64_t end = 0;
        std::string soname;
        std::string path;
    };

    class mapsInfo {
    public:
        uint64_t base = 0;
        uint64_t end = 0;
        char path[256] = {};
        char flags[5] = {};
    };

    std::vector<soinfo> soList;
    std::vector<mapsInfo> mapsList;

    //libart.so     libandroid_runtime.so
    safeInfo() {
        const char *name1 = "libc.so";
        const char *name2 = "libdl.so";
        soList.push_back({0, 0, name1, ""});
        soList.push_back({0, 0, name2, ""});
    }

    void init() {
        int fd = openat_2("/proc/self/maps", O_RDONLY);
        if (fd <= 0) {
            LOGE("[safeInfo] failed to open maps");
            return;
        }

        readMaps(fd);
        close(fd);

        setSoList((uint64_t) fopen, &soList[0]);
        setSoList((uint64_t) dlsym, &soList[1]);

        auto test = getMapsInfo((uint64_t) anti);
        if (test.base > 0) {
            maps_changeA = false;
        }

        for (auto &i: soList) {
            LOGI("[safeInfo -> init] base:0x%" PRIx64" end:0x%" PRIx64" name:%-30s path:%s",
                 i.base, i.end, i.soname.c_str(), i.path.c_str());
        }
    }


    void readMaps(int fd) {
        char buf[1024] = {};

        if (fd <= 0) {
            return;
        }

        while (read_one_line(fd, buf, sizeof(buf)) > 0) {
            mapsInfo info;
            sscanf(buf, "%" PRIx64"-%" PRIx64" %s %*x %*x:%*x %*u %s\n",
                   &info.base, &info.end, info.flags, info.path);
            mapsList.push_back(info);
        }
    }


    bool setSoList(uint64_t fun, soinfo *soInfo) {
        auto info = getMapsInfo(fun);
        if (info.base == 0) {
            return false;
        }

        for (auto &i: mapsList) {
            if (strcmp(i.path, info.path) != 0) {
                continue;
            }

            if (memcmp((void *) i.base, ELFMAG, SELFMAG) == 0) {
                soInfo->base = i.base;
                soInfo->path = i.path;
            }

            if (i.end > soInfo->end) {
                soInfo->end = i.end;
            }
        }

        if (!soInfo->path.empty() && soInfo->base > 0 && soInfo->end > 0) {
            return true;
        }

        return false;
    }

    soinfo getSoInfo(const char *name) {
        soinfo info;
        for (auto &i: soList) {
            if (i.soname == name) {
                return i;
            }
        }
        return info;
    }

    mapsInfo getMapsInfo(uint64_t fun) {
        mapsInfo info;
        for (auto &i: mapsList) {
            if (i.base < fun && i.end > fun) {
                return i;
            }
        }
        return info;
    }
} si;


void thread_anti() {

}


void anti() {
    si.init();

    std::thread t1(thread_anti);
    t1.detach();
}






