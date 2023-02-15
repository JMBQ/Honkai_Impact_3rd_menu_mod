package com.android.support;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.content.pm.SigningInfo;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.util.Log;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MainActivity extends Activity {

//    static {
//        System.loadLibrary("JMBQ");
//    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getSignTest(getApplicationContext());
    }


    public static void getSignTest(Context context) {
        Log.i("JMBQ", "getSignatureOldAPI md5: " + md5(getSignatureOldAPI(context)));
        Log.i("JMBQ", "getSignatureNewAPI md5: " + md5(getSignatureNewAPI(context)));
        Log.i("JMBQ", "signature killed: " + PmsHook.killed);
    }


    private static byte[] getSignatureOldAPI(Context context) {
        try {
            @SuppressLint("PackageManagerGetSignatures")
            PackageInfo info = context.getPackageManager().getPackageInfo(context.getPackageName(),
                    PackageManager.GET_SIGNATURES);
            return info.signatures[0].toByteArray();
        } catch (PackageManager.NameNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    @TargetApi(Build.VERSION_CODES.P)
    private static byte[] getSignatureNewAPI(Context context) {
        PackageInfo packageInfo = null;
        Signature[] signs;

        try {
            packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(),
                    PackageManager.GET_SIGNING_CERTIFICATES);
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }

        SigningInfo signingInfo;
        if (packageInfo == null || (signingInfo = packageInfo.signingInfo) == null) {
            return null;
        }

        if (signingInfo.hasMultipleSigners()) {
            signs = signingInfo.getApkContentsSigners();
        } else {
            signs = signingInfo.getSigningCertificateHistory();
        }

        return signs[0].toByteArray();
    }


    private static String md5(byte[] bytes) {
        if (bytes == null) {
            return "null";
        }

        try {
            byte[] digest = MessageDigest.getInstance("MD5").digest(bytes);
            String hexDigits = "0123456789abcdef";
            char[] str = new char[digest.length * 2];
            int k = 0;
            for (byte b : digest) {
                str[k++] = hexDigits.charAt(b >>> 4 & 0xf);
                str[k++] = hexDigits.charAt(b & 0xf);
            }

            return new String(str);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

}
