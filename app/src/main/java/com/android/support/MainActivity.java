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
import android.util.Log;

public class MainActivity extends Activity {
    public static final String TAG = "JMBQ"; //Tag for logcat

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Context context = getApplicationContext();
        Log.i(TAG, "[onCreate] getGameOrigSignature: " +
                getGameOrigSignature(context, context.getPackageName()));
    }

    boolean getGameOrigSignature(Context context, String packageName) {
        StringBuilder sb = new StringBuilder();
        Signature[] signs;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            signs = getSignatureNewAPI(context, packageName);
        } else {
            signs = getSignatureOldAPI(context, packageName);
        }

        if (signs == null) {
            return false;
        }

        for (Signature sign : signs) {
            sb.append(sign.toCharsString());
        }

        //the signature of game
        Log.i(TAG, "OrigSignature: " + sb);

        return true;
    }

    private static Signature[] getSignatureOldAPI(Context context, String packageName) {
        try {
            @SuppressLint("PackageManagerGetSignatures")
            PackageInfo info = context.getPackageManager().getPackageInfo(packageName,
                    PackageManager.GET_SIGNATURES);
            return info.signatures;
        } catch (PackageManager.NameNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    @TargetApi(Build.VERSION_CODES.P)
    private static Signature[] getSignatureNewAPI(Context context, String packageName) {
        PackageInfo packageInfo = null;
        Signature[] signs;

        try {
            packageInfo = context.getPackageManager().getPackageInfo(packageName,
                    PackageManager.GET_SIGNING_CERTIFICATES);
        } catch (PackageManager.NameNotFoundException ignored) {
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

        return signs;
    }
}
