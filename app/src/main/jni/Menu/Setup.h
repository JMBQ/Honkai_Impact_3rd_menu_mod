#include <sstream>
#include <jni.h>
#include "Menu.h"

extern int api_level();

namespace ToastLength {
    inline const int LENGTH_LONG = 1;
    inline const int LENGTH_SHORT = 0;
}

//Jni stuff from MrDarkRX https://github.com/MrDarkRXx/DarkMod-Floating
void setDialog(jobject ctx, JNIEnv *env, const char *title, const char *msg) {
    //AlertDialog.Builder alert = new AlertDialog.Builder(context);
    auto clz_Alert = env->FindClass("android/app/AlertDialog$Builder");
    auto mid_init = env->GetMethodID(clz_Alert,
                                     "<init>",
                                     "(Landroid/content/Context;)V");
    auto obj_Alert = env->NewObject(clz_Alert, mid_init, ctx);

    //alert.setTitle(title)
    auto mid_setTitle = env->GetMethodID(clz_Alert,
                                         "setTitle",
                                         "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(obj_Alert, mid_setTitle, env->NewStringUTF(title));

    //alert.setMessage(msg)
    auto setMsg = env->GetMethodID(clz_Alert,
                                   "setMessage",
                                   "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(obj_Alert, setMsg, env->NewStringUTF(msg));

    //alert.setCancelable(false)
    auto setCa = env->GetMethodID(clz_Alert,
                                  "setCancelable",
                                  "(Z)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(obj_Alert, setCa, false);

    //alert.setPositiveButton("Ok", null)
    auto setPB = env->GetMethodID(clz_Alert,
                                  "setPositiveButton",
                                  "(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(obj_Alert, setPB,
                          env->NewStringUTF("Ok"),
                          static_cast<jobject>(NULL));

    //AlertDialog dialog = alert.create();
    auto mid_create = env->GetMethodID(clz_Alert,
                                       "create",
                                       "()Landroid/app/AlertDialog;");
    auto create_obj = env->CallObjectMethod(obj_Alert, mid_create);

    //dialog.show()
    auto AlertN = env->FindClass("android/app/AlertDialog");
    auto show = env->GetMethodID(AlertN, "show", "()V");
    env->CallVoidMethod(create_obj, show);
}

//主进程toast
void Toast(JNIEnv *env, jobject thiz, const char *text, int length) {
    auto clz_Toast = env->FindClass("android/widget/Toast");
    auto mid_makeText = env->GetStaticMethodID(clz_Toast,
                                               "makeText",
                                               "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    auto obj_toast = env->CallStaticObjectMethod(clz_Toast,
                                                 mid_makeText,
                                                 thiz,
                                                 env->NewStringUTF(text),
                                                 length);
    auto mid_show = env->GetMethodID(clz_Toast, "show", "()V");
    env->CallVoidMethod(obj_toast, mid_show);
}

//跳转至悬浮权限界面
void startActivityPermission(JNIEnv *env, jobject ctx) {
    //Intent intent = new Intent();
    auto clz_Intent = env->FindClass("android/content/Intent");
    auto newIntent = env->GetMethodID(clz_Intent, "<init>", "()V");
    auto intent = env->NewObject(clz_Intent, newIntent);

    //intent.setAction(Settings.ACTION_MANAGE_OVERLAY_PERMISSION);
    auto mid_setAction = env->GetMethodID(clz_Intent, "setAction",
                                          "(Ljava/lang/String;)Landroid/content/Intent;");
    env->CallObjectMethod(intent,
                          mid_setAction,
                          env->NewStringUTF(
                                  "android.settings.action.MANAGE_OVERLAY_PERMISSION"));
    //context.startActivity(intent);
    auto clz_context = env->GetObjectClass(ctx);
    auto mid_startActivity = env->GetMethodID(clz_context,
                                              "startActivity",
                                              "(Landroid/content/Intent;)V");
    env->CallVoidMethod(ctx, mid_startActivity, intent);
}

//悬浮窗服务
void startService(JNIEnv *env, jobject ctx) {
    auto native_context = env->GetObjectClass(ctx);
    auto intentClass = env->FindClass("android/content/Intent");
    auto actionString = env->FindClass("com/android/support/Launcher");
    auto newIntent = env->GetMethodID(intentClass,
                                      "<init>",
                                      "(Landroid/content/Context;Ljava/lang/Class;)V");
    auto intent = env->NewObject(intentClass, newIntent, ctx, actionString);
    auto startActivityMethodId = env->GetMethodID(native_context,
                                                  "startService",
                                                  "(Landroid/content/Intent;)Landroid/content/ComponentName;");

    env->CallObjectMethod(ctx, startActivityMethodId, intent);
}

//Needed jclass parameter because this is a static java method
void CheckOverlayPermission(JNIEnv *env, jclass, jobject ctx) {
    //If overlay permission option is greyed out, make sure to add android.permission.SYSTEM_ALERT_WINDOW in manifest
    if (api_level() >= 23) { //Android 6.0
        jclass Settings = env->FindClass("android/provider/Settings");
        jmethodID canDraw = env->GetStaticMethodID(Settings,
                                                   "canDrawOverlays",
                                                   "(Landroid/content/Context;)Z");
        if (!env->CallStaticBooleanMethod(Settings, canDraw, ctx)) {
            startActivityPermission(env, ctx);
            return;
        }
    }

    startService(env, ctx);
}

void Init(JNIEnv *env, jobject, jobject ctx, jobject title, jobject subtitle) {
    //Set sub title
    setText(env, title, "<b>Modded by JMBQ</b>");

    //Set sub title
    setText(env, subtitle,
            "<b><p style=\"color:green;\">Please open the features after the login interface appears  请在出现登陆界面之后再开启功能</p></b>");

    //setDialog(ctx,env,"Title"),"Message Example"));
    Toast(env, ctx, "JMBQ：free and no ads", ToastLength::LENGTH_LONG);

    initValid = true;
}