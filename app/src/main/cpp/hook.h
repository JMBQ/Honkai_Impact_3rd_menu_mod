#pragma once

#include <jni.h>
#include <string>


class Cheat {
public:
    uint64_t offset = 0;
    bool found = false;
};

#define HOOK_DEF(ret, func, ...) \
  ret (*orig_##func)(__VA_ARGS__); \
  ret new_##func(__VA_ARGS__)

int api_level();
void hack_thread();