# Honkai Impact 3 mod

针对 崩坏3rd 的悬浮菜单mod

## 特点
1. 适用于国外区服
2. 动态抓取offset，故适用于当前及以后的基本游戏版本
3. 适配arm64-v8a、armeabi-v7a
4. 适用于安卓手机、安卓模拟器（主流模拟器会调用armeabi-v7a架构）
5. 不夹带私货（比如 广告）

## 食用方法
详情见 tutorial.docx

  1.  反编译游戏apk，生成对应文件夹
  2.  添加悬浮权限	<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
  3.  添加悬浮窗服务	<service		android:name="com.android.support.Launcher"		android:enabled="true" 	android:exported="false" 	android:stopWithTask="true"/>
  4.  将com\android\support里的所有smali文件放入游戏文件夹中的android\support
  5.  打开com\miHoYo\overridenativeactivity\OverrideNativeActivity.smali，找到onCreate方法，在方法开头插入invoke-static {p0}, Lcom/android/support/Main;->Start(Landroid/content/Context;)V
  6.  将libSaber、libArcher这2个文件放入游戏目录assets文件夹内
  7.  编译游戏文件夹，生成直装包
