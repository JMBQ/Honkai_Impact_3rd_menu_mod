
#include <jni.h>
#include <cstring>
#include <cstdio>


static char *ByteArrayToChar(JNIEnv *env, jbyteArray ba) {
    jbyte *bytes = env->GetByteArrayElements(ba, nullptr);
    int arrayLength = env->GetArrayLength(ba);

    static char str[64] = {};
    memset(str, 0, sizeof(str));
    memcpy(str, bytes, arrayLength);

    env->ReleaseByteArrayElements(ba, bytes, 0);

    return str;
}

// 安卓9以上，api方式获取签名
const char *getCustomSign(JNIEnv *env, jobject context, const char *package_name) {
    if (package_name == nullptr) {
        return "null";
    }
    // PackageManager pm = mContext.getPackageManager();
    auto clz_context = env->FindClass("android/content/Context");
    auto mid_getPackageManager = env->GetMethodID(clz_context,
                                                  "getPackageManager",
                                                  "()Landroid/content/pm/PackageManager;");
    auto obj_getPackageManager = env->CallObjectMethod(context, mid_getPackageManager);

    // PackageInfo obj_getPackageManager = pm.getPackageInfo(str, PackageManager.GET_SIGNING_CERTIFICATES);
    auto clz_getPackageManager = env->GetObjectClass(obj_getPackageManager);
    auto mid_getPackageInfo = env->GetMethodID(clz_getPackageManager,
                                               "getPackageInfo",
                                               "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    auto obj_getPackageInfo = env->CallObjectMethod(obj_getPackageManager,
                                                    mid_getPackageInfo,
                                                    env->NewStringUTF(package_name),
                                                    0x8000000);

    // SigningInfo signingInfo = packageInfo.signingInfo;
    auto clz_signingInfo = env->GetObjectClass(obj_getPackageInfo);
    auto fid_signingInfo = env->GetFieldID(clz_signingInfo,
                                           "signingInfo",
                                           "Landroid/content/pm/SigningInfo;");
    auto obj_signingInfo = env->GetObjectField(obj_getPackageInfo, fid_signingInfo);

    // Signature[] signs = signingInfo.getApkContentsSigners();
    auto Apk_clazz = env->FindClass("android/content/pm/SigningInfo");
    auto mid_getApkContentsSigners = env->GetMethodID(Apk_clazz,
                                                      "getApkContentsSigners",
                                                      "()[Landroid/content/pm/Signature;");
    auto signs = (jobjectArray) env->CallObjectMethod(obj_signingInfo,
                                                      mid_getApkContentsSigners);

    // Signature signature = signs[0];
    auto sign = env->GetObjectArrayElement(signs, 0);

    // MessageDigest instance = MessageDigest.mid_getInstance("md5");
    auto clz_MessageDigest = env->FindClass("java/security/MessageDigest");
    auto mid_getInstance = env->GetStaticMethodID(clz_MessageDigest,
                                                  "getInstance",
                                                  "(Ljava/lang/String;)Ljava/security/MessageDigest;");
    auto obj_instance = env->CallStaticObjectMethod(clz_MessageDigest,
                                                    mid_getInstance,
                                                    env->NewStringUTF("md5"));

    // instance.mid_update(signature.toByteArray());
    auto clz_Signature = env->FindClass("android/content/pm/Signature");
    auto mid_toByteArray = env->GetMethodID(clz_Signature,
                                            "toByteArray",
                                            "()[B");
    auto obj_arr = env->CallObjectMethod(sign, mid_toByteArray);
    auto mid_update = env->GetMethodID(clz_MessageDigest,
                                       "update",
                                       "([B)V");
    env->CallVoidMethod(obj_instance, mid_update, obj_arr);

    // byte[] digest = instance.digest();
    auto mid_digest = env->GetMethodID(clz_MessageDigest,
                                       "digest",
                                       "()[B");
    auto obj_digest = (jbyteArray) env->CallObjectMethod(obj_instance, mid_digest);

    char tmp[128] = {};
    sprintf(tmp, "%s", ByteArrayToChar(env, obj_digest));

    static char str[128] = {};
    memset(str, 0, sizeof(str));
    for (int i = 0; i < strlen(tmp); ++i) {
        sprintf(str, "%s%02x", str, tmp[i] & 255);
    }

    return str;
}
