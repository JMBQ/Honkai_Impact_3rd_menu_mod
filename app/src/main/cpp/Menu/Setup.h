#include <sstream>
#include <jni.h>
#include "Menu.h"
#include "../log.h"

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


void Init(JNIEnv *env, jobject, jobject ctx, jobject title, jobject subtitle) {
    //Set sub title
    setText(env, title, "<b>Modded by JMBQ</b>");

    //Set sub title
    setText(env, subtitle,
            "<b><p style=\"color:green;\">Please open the features after the login interface appears</p></b>");

    //setDialog(ctx,env,"Title","Message Example");
    Toast(env, ctx, "JMBQ: free and no ads", ToastLength::LENGTH_LONG);

    initValid = true;
}
