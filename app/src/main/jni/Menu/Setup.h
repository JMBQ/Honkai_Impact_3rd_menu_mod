#include <sstream>
#include "Menu.h"
#include "../obfuscate.h"

namespace ToastLength {
    inline const int LENGTH_LONG = 1;
    inline const int LENGTH_SHORT = 0;
}

//Jni stuff from MrDarkRX https://github.com/MrDarkRXx/DarkMod-Floating
void setDialog(jobject ctx, JNIEnv *env, const char *title, const char *msg) {
    //AlertDialog.Builder alert = new AlertDialog.Builder(context);
    auto clz_Alert = env->FindClass(obf("android/app/AlertDialog$Builder"));
    auto mid_init = env->GetMethodID(clz_Alert,
                                     obf("<init>"),
                                     obf("(Landroid/content/Context;)V"));
    auto obj_Alert = env->NewObject(clz_Alert, mid_init, ctx);

    //alert.setTitle(title)
    auto mid_setTitle = env->GetMethodID(clz_Alert,
                                         obf("setTitle"),
                                         obf("(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(obj_Alert, mid_setTitle, env->NewStringUTF(title));

    //alert.setMessage(msg)
    auto setMsg = env->GetMethodID(clz_Alert,
                                   obf("setMessage"),
                                   obf("(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(obj_Alert, setMsg, env->NewStringUTF(msg));

    //alert.setCancelable(false)
    auto setCa = env->GetMethodID(clz_Alert,
                                  obf("setCancelable"),
                                  obf("(Z)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(obj_Alert, setCa, false);

    //alert.setPositiveButton("Ok", null)
    auto setPB = env->GetMethodID(clz_Alert,
                                  obf("setPositiveButton"),
                                  obf("(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;"));
    env->CallObjectMethod(obj_Alert, setPB,
                          env->NewStringUTF("Ok"),
                          static_cast<jobject>(NULL));

    //AlertDialog dialog = alert.create();
    auto mid_create = env->GetMethodID(clz_Alert,
                                       obf("create"),
                                       obf("()Landroid/app/AlertDialog;"));
    auto create_obj = env->CallObjectMethod(obj_Alert, mid_create);

    //dialog.show()
    auto AlertN = env->FindClass(obf("android/app/AlertDialog"));
    auto show = env->GetMethodID(AlertN, obf("show"), obf("()V"));
    env->CallVoidMethod(create_obj, show);
}

//主进程toast
void Toast(JNIEnv *env, jobject thiz, const char *text, int length) {
    auto clz_Toast = env->FindClass(obf("android/widget/Toast"));
    auto mid_makeText = env->GetStaticMethodID(clz_Toast,
                                               obf("makeText"),
                                               obf("(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"));
    auto obj_toast = env->CallStaticObjectMethod(clz_Toast,
                                                 mid_makeText,
                                                 thiz,
                                                 env->NewStringUTF(text),
                                                 length);
    auto mid_show = env->GetMethodID(clz_Toast, obf("show"), obf("()V"));
    env->CallVoidMethod(obj_toast, mid_show);
}

//设置权限
void startActivityPermisson(JNIEnv *env, jobject ctx) {
    auto clz_context = env->GetObjectClass(ctx);
    auto mid_startActivity = env->GetMethodID(clz_context,
                                              obf("startActivity"),
                                              obf("(Landroid/content/Intent;)V"));

    auto mid_getPackageName = env->GetMethodID(clz_context,
                                               obf("getPackageName"),
                                               obf("()Ljava/lang/String;"));
    auto packageName_ = (jstring) env->CallObjectMethod(ctx, mid_getPackageName);

    const char *pkg = env->GetStringUTFChars(packageName_, 0);

    std::stringstream stream;
    stream << obf("package:");
    stream << pkg;
    std::string pakg = stream.str();

    auto clz_Uri = env->FindClass(obf("android/net/Uri"));
    auto mid_parse = env->GetStaticMethodID(clz_Uri,
                                            obf("parse"),
                                            obf("(Ljava/lang/String;)Landroid/net/Uri;"));
    auto UriMethod = env->CallStaticObjectMethod(clz_Uri,
                                                 mid_parse,
                                                 env->NewStringUTF(pakg.c_str()));

    auto clz_Intent = env->FindClass(obf("android/content/Intent"));
    auto newIntent = env->GetMethodID(clz_Intent,
                                      obf("<init>"),
                                      obf("(Ljava/lang/String;Landroid/net/Uri;)V"));
    jobject intent = env->NewObject(clz_Intent,
                                    newIntent,
                                    env->NewStringUTF(
                                            obf("android.settings.action.MANAGE_OVERLAY_PERMISSION")),
                                    UriMethod);

    env->CallVoidMethod(ctx, mid_startActivity, intent);
}

//悬浮窗服务
void startService(JNIEnv *env, jobject ctx) {
    auto native_context = env->GetObjectClass(ctx);
    auto intentClass = env->FindClass(obf("android/content/Intent"));
    auto actionString = env->FindClass(obf("com/android/support/Launcher"));
    auto newIntent = env->GetMethodID(intentClass,
                                      obf("<init>"),
                                      obf("(Landroid/content/Context;Ljava/lang/Class;)V"));
    auto intent = env->NewObject(intentClass, newIntent, ctx, actionString);
    auto startActivityMethodId = env->GetMethodID(native_context,
                                                  obf("startService"),
                                                  obf("(Landroid/content/Intent;)Landroid/content/ComponentName;"));

    env->CallObjectMethod(ctx, startActivityMethodId, intent);
}


static int api_level() {
    char value[92] = {0};
    if (__system_property_get("ro.build.version.sdk", value) < 1) return -1;
    int api_level = atoi(value);
    return (api_level > 0) ? api_level : -1;
}

//Needed jclass parameter because this is a static java method
void CheckOverlayPermission(JNIEnv *env, jclass, jobject ctx) {
    //If overlay permission option is greyed out, make sure to add android.permission.SYSTEM_ALERT_WINDOW in manifest
    if (api_level() >= 23) { //Android 6.0
        jclass Settings = env->FindClass(obf("android/provider/Settings"));
        jmethodID canDraw = env->GetStaticMethodID(Settings,
                                                   obf("canDrawOverlays"),
                                                   obf("(Landroid/content/Context;)Z"));
        if (!env->CallStaticBooleanMethod(Settings, canDraw, ctx)) {
            Toast(env, ctx,
                  obf("Overlay permission is required in order to show mod menu."),
                  ToastLength::LENGTH_LONG);
            startActivityPermisson(env, ctx);
            return;
        }
    }

    startService(env, ctx);
}

void Init(JNIEnv *env, jobject, jobject ctx, jobject title, jobject subtitle) {
    //Set sub title
    setText(env, title, obf("<b>Modded by JMBQ</b>"));

    //Set sub title
    setText(env, subtitle,
            obf("<b><p style=\"color:green;\">Please open the function after the login interface appears  请在出现登陆界面之后再开启功能</p></b>"));

    //setDialog(ctx,env,obf("Title"),obf("Message Example"));
    Toast(env, ctx, obf("JMBQ：free and no ads"), ToastLength::LENGTH_LONG);

    initValid = true;
}