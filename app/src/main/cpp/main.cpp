
#include <jni.h>
#include <unistd.h>
#include <thread>

#include "Menu/Setup.h"
#include "hook.h"
#include "log.h"
#include <dobby.h>

extern uint64_t il2cpp_base;
extern Cheat cheat[];


// NameSpace: ns_aaa
// class: clz_aaa
// public boolean finish() ;
bool fs = false;
HOOK_DEF(bool , full) {
    if (fs) {
        return fs;
    } else {
        return orig_full();
    }
}


// NameSpace: ns_bbb
// class: clz_bbb
// public single getMoveSpeedRate(single ratio) ;
bool ms = false;
HOOK_DEF(float, move, float ratio) {
    if (ms) {
        return 2.0;
    } else {
        return orig_move(ratio);
    }
}

// NameSpace: ns_ccc
// class: clz_ccc
// public single getAttackSpeedRate() ;
bool as = false;
HOOK_DEF(float, atkSpeed) {
    if (as) {
        return 2.0;
    } else {
        return orig_atkSpeed();
    }
}

// NameSpace: ns_ddd
// class: clz_ddd
// public single getSPRate(single ratio) ;
bool sp = false;
HOOK_DEF(float, SP, float ratio) {
    if (sp) {
        return 2.0;
    } else {
        return orig_SP(ratio);
    }
}


// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box

jobjectArray GetFeatureList(JNIEnv *env, [[maybe_unused]] jobject context) {
    jobjectArray ret;

    const char *features[] = {
//            "Category_功能/the Category", //Not counted
            "Toggle_features1",
            "Toggle_features2",
            "Toggle_features3",
            "Toggle_features4",
//            "100_Toggle_True_The toggle 2", //This one have feature number assigned, and switched on by default
//            "110_Toggle_The toggle 3", //This one too
//            "SeekBar_The slider_1_100",
//            "SeekBar_Kittymemory slider example_1_5",
//            "Spinner_The spinner_Items 1,Items 2,Items 3",
//            "Button_The button",
//            "ButtonLink_The button with link_https://www.youtube.com/", //Not counted
//            "ButtonOnOff_The On/Off button",
//            "CheckBox_The Check Box",
//            "InputValue_Input number",
//            "InputValue_1000_Input number 2", //Max value
//            "InputText_Input text",
//            "RadioButton_Radio buttons_OFF,Mod 1,Mod 2,Mod 3",

//            //Create new collapse
//            "Collapse_Collapse 1",
//            "CollapseAdd_Toggle_The toggle",
//            "CollapseAdd_Toggle_The toggle",
//            "123_CollapseAdd_Toggle_The toggle",
//            "122_CollapseAdd_CheckBox_Check box",
//            "CollapseAdd_Button_The button",
//
//            //Create new collapse again
//            "Collapse_Collapse 2_True",
//            "CollapseAdd_SeekBar_The slider_1_100",
//            "CollapseAdd_InputValue_Input number",

            "RichTextView_https://github.com/JMBQ"
//            "RichWebView_<html><head><style>body{color: white;}</style></head><body>"
//                      "This is WebView, with REAL HTML support!"
//                      "<div style=\"background-color: darkblue; text-align: center;\">Support CSS</div>"
//                      "<marquee style=\"color: green; font-weight:bold;\" direction=\"left\" scrollamount=\"5\" behavior=\"scroll\">This is <u>scrollable</u> text</marquee>"
//                      "</body></html>"
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = env->NewObjectArray(Total_Feature,
                              env->FindClass("java/lang/String"),
                              env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

int Changes(JNIEnv*, jclass, jobject, jint featNum, jstring featName, jint value,
            jboolean boolean, jstring str) {
    static bool has_hook_method = false;
    static bool hook_0 = false;
    static bool hook_1 = false;
    static bool hook_2 = false;
    static bool hook_3 = false;
    int result = -1;

    if (il2cpp_base < 0x8000) {
        return -1;  //wait
    }

    if (!cheat[featNum].found) {
        return 0;   //fail
    }

//    //LOGI("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s",
//         featNum,
//         env->GetStringUTFChars(featName, nullptr),
//         value,
//         boolean,
//         str != nullptr ? env->GetStringUTFChars(str, nullptr) : "");
    if (!has_hook_method) {
        if (cheat[0].offset > 0) {
            hook_0 = (DobbyHook((void *)(il2cpp_base + cheat[0].offset),
                      (dobby_dummy_func_t) new_full,
                      (dobby_dummy_func_t*) &orig_full) == 0);
        }
        if (cheat[1].offset > 0) {
            hook_1 = (DobbyHook((void *)(il2cpp_base + cheat[1].offset),
                      (dobby_dummy_func_t) new_move,
                      (dobby_dummy_func_t*) &orig_move) == 0);
        }
        if (cheat[2].offset > 0) {
            hook_2 = (DobbyHook((void *)(il2cpp_base + cheat[2].offset),
                      (dobby_dummy_func_t) new_atkSpeed,
                      (dobby_dummy_func_t*) &orig_atkSpeed) == 0);
        }
        if (cheat[3].offset > 0) {
            hook_3 = (DobbyHook((void *)(il2cpp_base + cheat[3].offset),
                      (dobby_dummy_func_t) new_SP,
                      (dobby_dummy_func_t*) &orig_SP) == 0);
        }
        has_hook_method = true;
    }

    switch (featNum) {
        case 0: //full star
            fs = boolean;
            result = hook_0;
            break;
        case 1: //move speed
            ms = boolean;
            result = hook_1;
            break;
        case 2: //atk speed
            as = boolean;
            result = hook_2;
            break;
        case 3: //get Multiplier SP
            sp = boolean;
            result = hook_3;
            break;
        default:
            break;
    }

    return result;
}

jboolean IsGameLibLoaded(JNIEnv *, jobject) {
    return il2cpp_base > 0x8000;
}


uintptr_t string2Offset(const char *str) {
    return strtoul(str, nullptr, 16);
}


int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {"Icon",            "()Ljava/lang/String;",                                                           (void *) Icon},
            {"IconWebViewData", "()Ljava/lang/String;",                                                           (void *) IconWebViewData},
            {"IsGameLibLoaded", "()Z",                                                                            (void *) IsGameLibLoaded},
            {"Init",            "(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V", (void *) Init},
            {"SettingsList",    "()[Ljava/lang/String;",                                                          (void *) SettingsList},
            {"GetFeatureList",  "()[Ljava/lang/String;",                                                          (void *) GetFeatureList},
    };

    jclass clazz = env->FindClass("com/android/support/Menu");
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}


int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {"Changes",
             "(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)I",
             (void *) Changes},
    };

    jclass clazz = env->FindClass("com/android/support/Preferences");
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0 || RegisterPreferences(env) != 0) {
        return JNI_ERR;
    }

    std::thread t1(hack_thread);
    t1.detach();

    return JNI_VERSION_1_6;
}

