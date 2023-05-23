## [English version](README_EN.md)
![image](img/01.jpg)
  
## 设备要求
* 安卓9或更高
* 如果设备已root，需要对游戏隐藏root，否则可能会提示“非官方安装包”
  
## 特点
* 适配国外区服, 包括且不限sea, global, jp, kr, tw, vn
* 适配安卓64位手机, 无需root
* 适配arm64-v8a架构 (64位)
* 支持绕过普通签名校验
* 动态抓取游戏功能，适用当前及以后的游戏版本
* 没有广告
* 简中服玩家看页尾
  
## 模拟器
* 不再支持32位模拟器
* 仅推荐64位夜神模拟器9 (nox9)
  
## 食用
* 只推荐使用apkeasytool工具
* 反编译游戏官方apk完毕后自动生成游戏文件夹
* 修改AndroidManifest.xml
  * 添加悬浮窗权限, 添加悬浮窗服务
  ```
  <service android:name="com.android.support.Launcher" android:enabled="true" android:exported="false" android:stopWithTask="true"/>

  <uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
  ```
  ![image](img/02.jpg)
  <br></br>
  * 将 ```androidx.core.app.CoreComponentFactory``` 替换成 ```com.android.support.Main```

* 编译游戏文件夹，生成apk文件，这里简称 P
* 使用压缩软件(如winrar)打开官方apk，将一级目录里的dex全部提取出来。这步是为了绕过dex校验，无论你之前是否修改过smali文件，打包后dex文件会发生改变，我们需要还原这个，star rail也可以这样绕过检验
* 使用压缩软件打开P，将提取出来的dex文件和我给的assets、classes4.dex都复制到P里面。提取出来的dex名称不能和我给的dex名称重复，若出现重复，修改我的dex为classes5.dex
* 对P进行zipAlign操作（自动附带签名），生成真正的菜单模块apk


https://github.com/JMBQ/Honkai_Impact_3rd_menu_mod/assets/78288131/1570ba6b-9c17-4dca-abe4-db212ccacc66



## 注意
* 首次运行游戏，在正常情况下会跳至悬浮权限界面
* 刚打开游戏就闪退
  * 偶尔出现刚打开就闪退 属于正常现象
  * 连续多次出现刚打开就闪退 属于不正常现象，检查是否存在错误操作

## 最后
* 该mod不适合简中服(有多重签名校验)
* 如果你手机已解锁bootloader，可以使用 [U.R.C](https://github.com/JMBQ/URC)，适用所有区服
* 已提供简中服6.5版本直装破解包
