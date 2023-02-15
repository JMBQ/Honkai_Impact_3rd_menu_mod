#pragma once

#include <jni.h>
#include <android/log.h>
#include <string>

#define LOG_TAG "JMBQ"

class Cheat {
public:
    uint32_t offset = 0;
    bool found = false;
};

#define HOOK_DEF(ret, func, ...) \
  ret (*orig_##func)(__VA_ARGS__); \
  ret new_##func(__VA_ARGS__)


#define LOGE(...) {                                                     \
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);   \
}

#define LOGI(...) {                                                     \
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);    \
}

void *hack_thread(void *);
const char *getCustomSign(JNIEnv *env, jobject context, const char* package_name);