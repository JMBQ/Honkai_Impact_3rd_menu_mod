
#include <jni.h>
#include <unistd.h>

#include "Menu/Setup.h"
#include "hook.h"
#include "obfuscate.h"
#include <dobby.h>

extern uint64_t il2cpp_base;
extern Cheat cheat[];

static bool fs = false;
HOOK_DEF(bool , full, void *thiz) {
    return fs;
}

static bool as = false;
HOOK_DEF(float, atkSpeed, void *thiz) {
    if (as) {
        return 2.5;
    } else {
        return orig_atkSpeed(thiz);
    }
}

HOOK_DEF(float, move, float ratio, void *thiz) {
    return 3.5;
}

static bool sp = false;
HOOK_DEF(float, SP, float ratio, void *thiz) {
    if (sp) {
        return 2.0;
    } else {
        return orig_SP(ratio, thiz);
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
//            obf("Category_功能/the Category"), //Not counted
            obf("Toggle_满星 / always full star"),
            obf("Toggle_定怪 / monster AI"),
            obf("Toggle_攻速 / attackSpeed"),
            obf("Toggle_能量 / get Multiplier SP"),
//            obf("100_Toggle_True_The toggle 2"), //This one have feature number assigned, and switched on by default
//            obf("110_Toggle_The toggle 3"), //This one too
//            obf("SeekBar_The slider_1_100"),
//            obf("SeekBar_Kittymemory slider example_1_5"),
//            obf("Spinner_The spinner_Items 1,Items 2,Items 3"),
//            obf("Button_The button"),
//            obf("ButtonLink_The button with link_https://www.youtube.com/"), //Not counted
//            obf("ButtonOnOff_The On/Off button"),
//            obf("CheckBox_The Check Box"),
//            obf("InputValue_Input number"),
//            obf("InputValue_1000_Input number 2"), //Max value
//            obf("InputText_Input text"),
//            obf("RadioButton_Radio buttons_OFF,Mod 1,Mod 2,Mod 3"),

//            //Create new collapse
//            obf("Collapse_Collapse 1"),
//            obf("CollapseAdd_Toggle_The toggle"),
//            obf("CollapseAdd_Toggle_The toggle"),
//            obf("123_CollapseAdd_Toggle_The toggle"),
//            obf("122_CollapseAdd_CheckBox_Check box"),
//            obf("CollapseAdd_Button_The button"),
//
//            //Create new collapse again
//            obf("Collapse_Collapse 2_True"),
//            obf("CollapseAdd_SeekBar_The slider_1_100"),
//            obf("CollapseAdd_InputValue_Input number"),

            obf("RichTextView_https://github.com/JMBQ")
//            obf("RichWebView_<html><head><style>body{color: white;}</style></head><body>"
//                      "This is WebView, with REAL HTML support!"
//                      "<div style=\"background-color: darkblue; text-align: center;\">Support CSS</div>"
//                      "<marquee style=\"color: green; font-weight:bold;\" direction=\"left\" scrollamount=\"5\" behavior=\"scroll\">This is <u>scrollable</u> text</marquee>"
//                      "</body></html>")
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = env->NewObjectArray(Total_Feature,
                              env->FindClass(obf("java/lang/String")),
                              env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

int Changes(JNIEnv*, jclass, jobject, jint featNum, jstring featName, jint value,
            jboolean boolean, jstring str) {

    if (il2cpp_base == 0) {
        return -1;
    }

    if (!cheat[featNum].found) {
        return 0;
    }

//    //LOGD(obf("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"),
//         featNum,
//         env->GetStringUTFChars(featName, nullptr),
//         value,
//         boolean,
//         str != nullptr ? env->GetStringUTFChars(str, nullptr) : "");

    switch (featNum) {
        case 0: //full star
            DobbyHook((void *)(il2cpp_base + cheat[0].offset),
                      (dobby_dummy_func_t) new_full,
                      (dobby_dummy_func_t*) &orig_full);
            fs = boolean;
            break;
        case 1: //ai

            break;
        case 2: //atk speed
            DobbyHook((void *)(il2cpp_base + cheat[2].offset),
                      (dobby_dummy_func_t) new_atkSpeed,
                      (dobby_dummy_func_t*) &orig_atkSpeed);
            as = boolean;
            break;
        case 3: //get Multiplier SP
            DobbyHook((void *)(il2cpp_base + cheat[3].offset),
                      (dobby_dummy_func_t) new_SP,
                      (dobby_dummy_func_t*) &orig_SP);
            sp = boolean;
            break;
        default:
            break;
    }

    return 1;
}

jboolean IsGameLibLoaded(JNIEnv *, jobject) {
    return il2cpp_base > 0;
}


uintptr_t string2Offset(const char *str) {
    return strtoul(str, nullptr, 16);
}

//__attribute__((constructor)) void lib_main() {
//
//}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {obf("Icon"),            obf("()Ljava/lang/String;"),                                                           (void *) Icon},
            {obf("IconWebViewData"), obf("()Ljava/lang/String;"),                                                           (void *) IconWebViewData},
            {obf("IsGameLibLoaded"), obf("()Z"),                                                                            (void *) IsGameLibLoaded},
            {obf("Init"),            obf("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), (void *) Init},
            {obf("SettingsList"),    obf("()[Ljava/lang/String;"),                                                          (void *) SettingsList},
            {obf("GetFeatureList"),  obf("()[Ljava/lang/String;"),                                                          (void *) GetFeatureList},
    };

    jclass clazz = env->FindClass(obf("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}


int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {obf("Changes"),
             obf("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)I"),
             (void *) Changes},
    };

    jclass clazz = env->FindClass(obf("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}


int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {obf("CheckOverlayPermission"),
             obf("(Landroid/content/Context;)V"),
             (void *) CheckOverlayPermission},
    };

    jclass clazz = env->FindClass(obf("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}


extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {    //void *reserved
    LOGI("-----------------------------JNI_OnLoad---------------------------------")
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0 || RegisterPreferences(env) != 0 || RegisterMain(env) != 0) {
        return JNI_ERR;
    }

    pthread_t tid;
    int ret = pthread_create(&tid, nullptr, hack_thread, nullptr);

    if (ret != 0) {
        //crashAPP();
    }

    return JNI_VERSION_1_6;
}

