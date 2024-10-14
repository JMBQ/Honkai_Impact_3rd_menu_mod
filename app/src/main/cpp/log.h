
#ifndef HONKAI_IMPACT_3RD_MENU_MOD_LOG_H
#define HONKAI_IMPACT_3RD_MENU_MOD_LOG_H

#include <android/log.h>

#define LOG_TAG "JMBQ"

#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#endif //HONKAI_IMPACT_3RD_MENU_MOD_LOG_H
