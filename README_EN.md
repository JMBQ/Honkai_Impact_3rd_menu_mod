![image](img/01.jpg)

## Device
* Android vesion 9 or higher
* If the device is rooted, you need to hide the root from the game, otherwise it may prompt "unofficial  package"

## Features
* Available for this servers, including SEA, GLOBAL, JP, KR, TW, VN
* Android 64-bit phones, no root required
* Compatible with arm64-v8a architecture
* Support for bypassing normal signature checks
* Dynamic capture function offset for current and future versions of the game
* No ads
  
## x86 Android Emulator
* 32-bit emulators are no longer supported
* Recommended for 64-bit nox9 only
  
## How to use
* only recommend using the apkeasytool
* The game folder is automatically generated after decompiling the official apk of the game
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
* Use a compression software (e.g. winrar) to open the official apk and extract all the dex from the first level directory. This step is to bypass the dex check, whether you have modified the smali file or not, the dex file will change after packing, we need to restore this, star rail can also bypass dex check by this way
* Open P using the compression software and copy the extracted dex file into P along with the assets and classes4.dex I have given you. The name of the extracted dex should not be duplicated with the name of the dex I gave, if it is, change my dex to classes5.dex
* Perform a zipAlign operation on P (automatically with a signature) to generate the real menu module apk

https://github.com/JMBQ/Honkai_Impact_3rd_menu_mod/assets/78288131/1570ba6b-9c17-4dca-abe4-db212ccacc66

## Cautions
* The first time you run the game, you will jump to the hover permission screen under normal circumstances
* Crash just after opening the game
  * Occasional crashes just after opening are normal
  * Crash just after opening several times in a row This is not normal, check for incorrect operation

## Finally
* If your phone is unlocked for bootloader, you can use [U.R.C](https://github.com/JMBQ/URC) for all servers
