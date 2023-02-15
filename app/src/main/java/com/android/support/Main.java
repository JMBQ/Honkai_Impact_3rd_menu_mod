package com.android.support;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.provider.Settings;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

@SuppressWarnings("all")
public class Main extends Application {
    private static final String TAG = "JMBQ";

    public static void loadElf(Context context) {
        String sourceName = "libSaber";
        String target = getFilesMD5(context.getApplicationInfo().sourceDir).substring(0, 8);
        String elfPath = context.getCacheDir() + "/" + target;
//        String elfPath = context.getCacheDir() + "/" + sourceName;
        Log.i(TAG, "elf_path: " + elfPath);

        copyAssetsFile(context, sourceName, elfPath);

        File elfFile = new File(elfPath);
        if (elfFile.exists()) {
            if (!elfFile.setExecutable(true)) {
                Toast.makeText(context,
                        "faild to set execute permission", Toast.LENGTH_LONG).show();
                return;
            }
        } else {
            Toast.makeText(context, "faild to copy elf", Toast.LENGTH_LONG).show();
            return;
        }

        System.load(elfPath);
    }

    /**
     * 手动构建 在任意运行时刻都能正确获取Context
     */
    @SuppressLint({"DiscouragedPrivateApi", "PrivateApi"})
    public static Context getContext() throws Exception {
        // 反射获取 ActivityThread 的 currentActivityThread 获取 mainThread
        Class<?> activityThreadClass = Class.forName("android.app.ActivityThread");
        Method currentActivityThreadMethod =
                activityThreadClass.getDeclaredMethod("currentActivityThread");
        currentActivityThreadMethod.setAccessible(true);
        Object mainThreadObj = currentActivityThreadMethod.invoke(null);

        // 反射获取 mainThread 实例中的 mBoundApplication 字段
        Field mBoundApplicationField = activityThreadClass.getDeclaredField("mBoundApplication");
        mBoundApplicationField.setAccessible(true);
        Object mBoundApplicationObj = mBoundApplicationField.get(mainThreadObj);

        // 获取 mBoundApplication 的 packageInfo 变量
        if (mBoundApplicationObj == null)
            throw new NullPointerException("mBoundApplicationObj null");
            
        Class<?> mBoundApplicationClass = mBoundApplicationObj.getClass();
        Field infoField = mBoundApplicationClass.getDeclaredField("info");
        infoField.setAccessible(true);
        Object packageInfoObj = infoField.get(mBoundApplicationObj);

        // 反射调用 ContextImpl.createAppContext(ActivityThread mainThread, LoadedApk packageInfo)
        if (mainThreadObj == null) throw new NullPointerException("mainThreadObj null");
        if (packageInfoObj == null) throw new NullPointerException("packageInfoObj null");

        Method createAppContextMethod = Class.forName("android.app.ContextImpl").getDeclaredMethod(
                "createAppContext",
                mainThreadObj.getClass(),
                packageInfoObj.getClass());
        createAppContextMethod.setAccessible(true);

        return (Context) createAppContextMethod.invoke(null, mainThreadObj, packageInfoObj);
    }


    private static native void CheckOverlayPermission(Context context);

    /**
     * sourceName assets里面的ELF名称
     * targetPath ELF库运行路径
     */
    @TargetApi(Build.VERSION_CODES.N)
    public static void copyAssetsFile(Context context, String sourceName, String targetPath) {
        try {
            File sourceFile = new File(context.getCacheDir() + "/" + sourceName);
            File targetFile = new File(targetPath);

            if (!targetFile.exists() || targetFile.length() == 0) {
                FileOutputStream fos = new FileOutputStream(sourceFile);
                InputStream is = context.getAssets().open(sourceName);
                byte[] buffer = new byte[1024];
                int len;
                while (-1 != (len = is.read(buffer))) {
                    fos.write(buffer, 0, len);
                }
                fos.flush();
                is.close();
                fos.close();

                if (sourceFile.exists()) {
                    sourceFile.renameTo(targetFile);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static String getFilesMD5(String path) {
        BigInteger md5;
        int len;
        try {
            byte[] buffer = new byte[8192];
            MessageDigest md = MessageDigest.getInstance("MD5");
            File file = new File(path);
            FileInputStream fis = new FileInputStream(file);

            while ((len = fis.read(buffer)) != -1) {
                md.update(buffer, 0, len);
            }
            fis.close();

            byte[] digest = md.digest();
            md5 = new BigInteger(1, digest);

            return md5.toString(16);
        } catch (NoSuchAlgorithmException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }


    public static void Start(Context context) {
        MainActivity.getSignTest(context);
        loadElf(context);
//        CrashHandler.init(context, false);
        CheckOverlayPermission(context);
    }

    public static void StartWithoutPermission(Context context) {
        CrashHandler.init(context, true);
        if (context instanceof Activity) {
            //Check if context is an Activity.
            Menu menu = new Menu(context);
            menu.SetWindowManagerActivity();
            menu.ShowMenu();
        } else {
            //Anything else, ask for permission
            CheckOverlayPermission(context);
        }
    }

    public void startLauncher(Context context) {
        startService(new Intent(context, Launcher.class));
    }

    @TargetApi(Build.VERSION_CODES.M)
    public void CheckOverlayPermission_java(Context context) {
        if (Build.VERSION.SDK_INT >= 23) {
            if (!Settings.canDrawOverlays(context)) {
                Toast.makeText(context, "Overlay permission is required in order to show mod menu.",
                        Toast.LENGTH_SHORT).show();
            }
        }

        startLauncher(context);
    }
}
