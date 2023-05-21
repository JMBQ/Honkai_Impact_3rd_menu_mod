# Honkai Impact 3 mod

<br>![image](img/01.jpg)</br>


   
## Features
* Available for this servers, including sea, global, jp, kr, tw, vn
* Android 64-bit phones, no root required
* Compatible with arm64-v8a architecture (64-bit)
* Support for bypassing normal signature checks
* Dynamic capture function offset for current and future versions of the game
* No advertising
  
## x86 Android Emulator
* 32-bit emulators are no longer supported
  * nox9 (64-bit), Recommendation 100%
  * ldplayer9 (64-bit), Recommendation50%
  * Other emulators not tested
  
## How to use
* I only recommend using the apkeasytool tool
* The game folder is automatically generated after decompiling the official apk of the game
<br></br>
<br></br>
* modify AndroidManifest.xml
  * Add SYSTEM_ALERT_WINDOW permissions, Add corresponding service
  ```
  <service android:name="com.android.support.Launcher" android:enabled="true" android:exported="false" android:stopWithTask="true"/>

  <uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
  ```
  ![image](img/02.jpg)
  <br></br>

  * Replace ```androidx.core.app.CoreComponentFactory``` with ```com.android.support.Main```
  <br></br>
* Use apkeasytool to compile the game folder and generate the apk file, referred to here as P
* Use a compression software (e.g. winrar) to open the official apk and extract all the dex from the first level directory. This step is to bypass the dex checksum, whether you have modified the smali file before or not, the dex file will change after packing, we need to restore this, star rail can also bypass the checksum this way
* Open P using the compression software and copy the extracted dex file into P along with the assets and classes4.dex I have given you. The name of the extracted dex should not be duplicated with the name of the dex I gave, if it is, change my dex to classes5.dex
* Perform a zipAlign operation on P (automatically with a signature) to generate the real menu module apk


## Cautions
* The first time you run the game, you will jump to the hover permission screen under normal circumstances
* Crash just after opening the game
  * Occasional crashes just after opening are normal
  * Crash just after opening several times in a row This is not normal, check for incorrect operation

## Finally
* If your phone is unlocked for bootloader, you can use [U.R.C](https://github.com/JMBQ/URC) for all servers
