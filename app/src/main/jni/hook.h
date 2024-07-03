#pragma once

#include <jni.h>
#include <string>


class Cheat {
public:
    uint32_t offset = 0;
    bool found = false;
};

#define HOOK_DEF(ret, func, ...) \
  ret (*orig_##func)(__VA_ARGS__); \
  ret new_##func(__VA_ARGS__)


void hack_thread();
const char *getCustomSign(JNIEnv *env, jobject context, const char* package_name);