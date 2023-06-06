## [English version](README_EN.md)
![image](img/01.jpg)
  
## hack进度
* ano保护比较难搞，它居然绕过了我创建的虚假路径，拿到真实路径来进行检测，我有几个破解思路，需要时间
* menu mod 最近没时间弄，就算弄出来，也不再具备通用性了，U.R.C代替它
* 如果你设备已root，我极度建议你使用[U.R.C](https://github.com/JMBQ/URC)，它和menu mod相比，既好用又安全
* 如果你设备没有root，我建议使用能开启Zygisk的虚拟app，在CN环境里，这样的app是存在的
  
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



## 注意
* 首次运行游戏，在正常情况下会跳至悬浮权限界面
* 刚打开游戏就闪退
  * 偶尔出现刚打开就闪退 属于正常现象
  * 连续多次出现刚打开就闪退 属于不正常现象，检查是否存在错误操作

## 最后
* 该mod不适合简中服(有多重签名校验)
* 如果你手机已解锁bootloader，可以使用 [U.R.C](https://github.com/JMBQ/URC)，适用所有区服
* 已提供简中服6.5版本直装破解包
