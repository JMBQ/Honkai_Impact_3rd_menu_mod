
package com.android.support;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.lang.Thread.UncaughtExceptionHandler;
import java.text.SimpleDateFormat;
import java.util.Date;

public final class CrashHandler {

    public static final UncaughtExceptionHandler DEFAULT_UNCAUGHT_EXCEPTION_HANDLER = Thread.getDefaultUncaughtExceptionHandler();

    public static void init(final Context app, final boolean overlayRequired) {
        Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {

            @Override
            public void uncaughtException(Thread thread, Throwable throwable) {
                Log.e("AppCrash", "Error just lunched ");
                try {
                    tryUncaughtException(thread, throwable);
                } catch (Throwable e) {
                    e.printStackTrace();
                    if (DEFAULT_UNCAUGHT_EXCEPTION_HANDLER != null)
                        DEFAULT_UNCAUGHT_EXCEPTION_HANDLER.uncaughtException(thread, throwable);
                    else
                        System.exit(2);
                }
            }

            private void tryUncaughtException(Thread thread, Throwable throwable) {
                Log.e("AppCrash", "Try saving log");

                @SuppressLint("SimpleDateFormat")
                final String time = new SimpleDateFormat("yyyy_MM_dd-HH_mm_ss").format(new Date());
                String fileName = "mod_menu_crash_" + time + ".txt";
                String dirName;

                if (Build.VERSION.SDK_INT >= 30) { //Android R. AIDE didn't support Build.VERSION_CODES.R
                    dirName = "/storage/emulated/0/Documents/";
                } else {
                    dirName = String.valueOf(app.getExternalFilesDir(null));
                }

                File crashFile = new File(dirName, fileName);

                String versionName = "unknown";
                long versionCode = 0;
                try {
                    PackageInfo packageInfo = app.getPackageManager().getPackageInfo(app.getPackageName(), 0);
                    versionName = packageInfo.versionName;
                    versionCode = Build.VERSION.SDK_INT >= 28 ? packageInfo.getLongVersionCode()
                            : packageInfo.versionCode;
                } catch (PackageManager.NameNotFoundException ignored) {
                }

                String fullStackTrace;
                {
                    StringWriter sw = new StringWriter();
                    PrintWriter pw = new PrintWriter(sw);
                    throwable.printStackTrace(pw);
                    fullStackTrace = sw.toString();
                    pw.close();
                }

                String errorLog = "************* Crash Head ****************\n" +
                        "Time Of Crash      : " + time + "\n" +
                        "Device Manufacturer: " + Build.MANUFACTURER + "\n" +
                        "Device Model       : " + Build.MODEL + "\n" +
                        "Android Version    : " + Build.VERSION.RELEASE + "\n" +
                        "Android SDK        : " + Build.VERSION.SDK_INT + "\n" +
                        "App VersionName    : " + versionName + "\n" +
                        "App VersionCode    : " + versionCode + "\n" +
                        "************* Crash Head ****************\n" +
                        "\n" + fullStackTrace;

                try {
                    writeFile(crashFile, errorLog);
                } catch (IOException ignored) {
                }

                Toast.makeText(app, "Game has crashed unexpectedly", Toast.LENGTH_LONG).show();
                Toast.makeText(app, "Log saved to: " + String.valueOf(crashFile).replace("/storage/emulated/0/", ""), Toast.LENGTH_LONG).show();

                Log.e("AppCrash", "Done");

                System.exit(2);
            }

            private void writeFile(File file, String content) throws IOException {
                File parentFile = file.getParentFile();
                if (parentFile != null && !parentFile.exists()) {
                    parentFile.mkdirs();
                }
                file.createNewFile();
                FileOutputStream fos = new FileOutputStream(file);
                fos.write(content.getBytes());
                try {
                    fos.close();
                } catch (IOException ignored) {
                }
            }
        });
    }
}

