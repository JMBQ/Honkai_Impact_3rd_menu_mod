package com.android.support;

import static com.android.support.Menu.TAG;
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
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Map;

@SuppressWarnings("all")
public class Main extends Application {

    public static void loadElf(Context context) {
        String assetsName = "libHI3";
        String target = getFileSha1(context.getApplicationInfo().sourceDir).substring(0, 8);
        String elfPath = context.getCacheDir() + "/" + target;
        Log.i(TAG, "elfPath: " + elfPath);

        copyAssetsFile(context, assetsName, elfPath);

        File elfFile = new File(elfPath);
        if (elfFile.exists()) {
            if (!elfFile.setExecutable(true)) {
                Toast.makeText(context,
                        "faild to set execute permission", Toast.LENGTH_LONG).show();
                return;
            }
        } else {
            Toast.makeText(context, "failed to copy elf", Toast.LENGTH_LONG).show();
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


    @TargetApi(Build.VERSION_CODES.N)
    public static void copyAssetsFile(Context context, String assetsName, String elfPath) {
        if (context == null || assetsName.isEmpty() || elfPath.isEmpty()) return;

        try {
            File sourceFile = new File(context.getCacheDir() + "/" + assetsName);
            File targetFile = new File(elfPath);

            if (!targetFile.exists() || targetFile.length() == 0) {
                FileOutputStream fos = new FileOutputStream(sourceFile);
                InputStream is = context.getAssets().open(assetsName);
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


    public static String getFileSha1(String filepath) {
        try {
            File file = new File(filepath);
            if (!file.exists()) {
                return null;
            }

            FileInputStream in = new FileInputStream(file);
            MessageDigest messagedigest = MessageDigest.getInstance("SHA-1");

            byte[] buffer = new byte[1024 * 128];
            int len;
            while ((len = in.read(buffer)) > 0) {
                messagedigest.update(buffer, 0, len);
            }

            StringBuilder sb = new StringBuilder();
            String s;
            for (byte b : messagedigest.digest()) {
                s = Integer.toHexString(b & 0xFF);
                if (s.length() == 1) sb.append("0");
                sb.append(s);
            }
            return sb.toString();
        } catch (NoSuchAlgorithmException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @SuppressLint({"DiscouragedPrivateApi", "PrivateApi"})
    public static Activity getCurrentActivity() {
        try {
            Class<?> activityThreadClass = Class.forName("android.app.ActivityThread");
            Object activityThread = activityThreadClass.getMethod("currentActivityThread").invoke(null);
            Field activitiesField = activityThreadClass.getDeclaredField("mActivities");
            activitiesField.setAccessible(true);
            Map<?, ?> activities = (Map<?, ?>) activitiesField.get(activityThread);
            assert activities != null;
            for (Object activityRecord : activities.values()) {
                Class<?> activityRecordClass = activityRecord.getClass();
                Field pausedField = activityRecordClass.getDeclaredField("paused");
                pausedField.setAccessible(true);
                if (!pausedField.getBoolean(activityRecord)) {
                    Field activityField = activityRecordClass.getDeclaredField("activity");
                    activityField.setAccessible(true);
                    return (Activity) activityField.get(activityRecord);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static void create_menu(Context context) {
        CrashHandler.init(context, false);
        new Thread(() -> {
            Context activity;
            try {
                do {
                    activity = getCurrentActivity();
                    Thread.sleep(100);
                } while (activity == null);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            //Log.i(TAG, "activity: " + activity);
            new Main().CheckOverlay_java(activity);
        }).start();
    }


    public static void Start() {
        try {
            Context context = getContext();
            if (context != null) {
                PmsHook.killPM(context);
                loadElf(context);
                create_menu(context);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @TargetApi(Build.VERSION_CODES.M)
    public void CheckOverlay_java(Context context) {
        if (Build.VERSION.SDK_INT >= 23) {
            if (!Settings.canDrawOverlays(context)) {
                Intent intent = new Intent();
                intent.setAction(Settings.ACTION_MANAGE_OVERLAY_PERMISSION);
                context.startActivity(intent);
                return;
            }
        }
        Intent intent = new Intent(context, Launcher.class);
        context.startService(intent);
    }
}
