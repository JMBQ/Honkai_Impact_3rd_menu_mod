package com.android.support;

import android.app.Application;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Build;
import android.os.Parcel;
import android.os.Parcelable;

import org.lsposed.hiddenapibypass.HiddenApiBypass;

import java.lang.reflect.Field;
import java.util.Map;

public class PmsHook extends Application {
    public static boolean killed = false;

    public static void killPM(Context context) {
        String packageName = context.getPackageName();

        /* MainActivity getGameOrigSignature method.*/
        String sign = "308203773082025fa00302010202040f07d894300d06092a864886f70d01010b0500306c3110300e06035504061307556e6b6e6f776e3110300e06035504081307556e6b6e6f776e3110300e06035504071307556e6b6e6f776e3110300e060355040a1307556e6b6e6f776e3110300e060355040b1307556e6b6e6f776e3110300e06035504031307556e6b6e6f776e301e170d3136303631343035343130395a170d3433313033313035343130395a306c3110300e06035504061307556e6b6e6f776e3110300e06035504081307556e6b6e6f776e3110300e06035504071307556e6b6e6f776e3110300e060355040a1307556e6b6e6f776e3110300e060355040b1307556e6b6e6f776e3110300e06035504031307556e6b6e6f776e30820122300d06092a864886f70d01010105000382010f003082010a028201010090d1b428a00ad335b03f91cd10c1274fcee9c51a4b110efa359b6534cca29afdbb01ffb6dcd0e775e6e1b5c259b48790a305b6da4e84b25157057567a9203bf56d304196c72e7e08c6ca8c86ee8aeffcbd755c77abdbe70c9f3c2d89cd8c6d88cd41debd7caaea0697545be2e1f1e140c8fbde78d54500e4ed6f3cf399a0093ad45fd45c64b4a8783d10cd3d3b1ea7ffd83d93909e2515bfd74735ee0f84c00b28288fe731d3b416eff73928224fbb46714b0f9b1cdeb4a39c743eb3f22ca6fbc5f6d6d61f4f16e42cf2c20cb3ed63338e628f6e34a593e6cdc619fe431099d3b6f9a0e9e4e2ea66f7108fef9e482616cbf9a23ca33781677872f952ab9fac470203010001a321301f301d0603551d0e041604149ad8b52d06eab8638235860126f9e59aad2cf25b300d06092a864886f70d01010b050003820101007de3fdc7e4bed981f807d8e0e7739230d6f1e6f358cd75c1e6495b916cc328ce44402d547e8db8b7df38ac675d83c6c5972232e0b8ee1103208ba9208617c736104823a0b16de1eb781fbe0b5d4541ceacc62a00b2d2e687a49dd0d233abd64838d22d2b6c2d86b37cec0771848ebffc618676b1e57bcf6ea7f49e6946355367eb451dda1c416d96787a5b218b68a8cffd94cb9bb5cea9b5b9bd48b8eecccb798471f302cd04ac9018dfadeaad7bc0ba8e6d7ab951b5e8576b02d7c931c369306720264ac498509a2eedcad7c56ad9d9f2ec97bdd8cc9b6d90955659e9519185a0ae7f6d66b21cda94c492abac61934b94418486144d237d2a103434ca95045c";
        Signature fakeSignature = new Signature(sign);

        Parcelable.Creator<PackageInfo> originalCreator = PackageInfo.CREATOR;
        Parcelable.Creator<PackageInfo> creator = new Parcelable.Creator<PackageInfo>() {
            @Override
            public PackageInfo createFromParcel(Parcel source) {
                PackageInfo packageInfo = originalCreator.createFromParcel(source);
                if (packageInfo.packageName.equals(packageName)) {
                    killed = true;
                    if (packageInfo.signatures != null && packageInfo.signatures.length > 0) {
                        packageInfo.signatures[0] = fakeSignature;
                    }

                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
                        if (packageInfo.signingInfo != null) {
                            Signature[] signaturesArray = packageInfo.signingInfo.getApkContentsSigners();
                            if (signaturesArray != null && signaturesArray.length > 0) {
                                signaturesArray[0] = fakeSignature;
                            }
                        }
                    }
                }
                return packageInfo;
            }

            @Override
            public PackageInfo[] newArray(int size) {
                return originalCreator.newArray(size);
            }
        };

        try {
            findField(PackageInfo.class, "CREATOR").set(null, creator);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            HiddenApiBypass.addHiddenApiExemptions("Landroid/os/Parcel;", "Landroid/content/pm", "Landroid/app");
        }

        try {
            Object cache = findField(PackageManager.class, "sPackageInfoCache").get(null);
            //noinspection ConstantConditions
            cache.getClass().getMethod("clear").invoke(cache);
        } catch (Throwable ignored) {
        }

        try {
            Map<?, ?> mCreators = (Map<?, ?>) findField(Parcel.class, "mCreators").get(null);
            //noinspection ConstantConditions
            mCreators.clear();
        } catch (Throwable ignored) {
        }

        try {
            Map<?, ?> sPairedCreators = (Map<?, ?>) findField(Parcel.class, "sPairedCreators").get(null);
            //noinspection ConstantConditions
            sPairedCreators.clear();
        } catch (Throwable ignored) {
        }
    }


    public static Field findField(Class<?> clazz, String fieldName) throws NoSuchFieldException {
        try {
            Field field = clazz.getDeclaredField(fieldName);
            field.setAccessible(true);
            return field;
        } catch (NoSuchFieldException e) {
            while (true) {
                clazz = clazz.getSuperclass();
                if (clazz == null || clazz.equals(Object.class)) {
                    break;
                }
                try {
                    Field field = clazz.getDeclaredField(fieldName);
                    field.setAccessible(true);
                    return field;
                } catch (NoSuchFieldException ignored) {
                }
            }
            throw e;
        }
    }
}
