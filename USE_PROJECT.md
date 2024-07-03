
## 如何使用本项目源码

* 生成apk文件
    * 下载源码，使用android studio打开
    * 如果是局域网用户（CN），修改根目录下的build.gradle， 将CN version下面的注释取消掉，这样就可以使用阿里云镜像下载对应依赖库了
* 反编译生成的apk文件，得到菜单项目的smali文件夹、so文件
* 反编译游戏apk文件，得到游戏项目文件夹
* 将菜单项目的smali文件夹下的文件，拷贝到游戏项目文件夹下的smali目录（如果有多个smali目录，一般放在最后一个）
* 将菜单项目的so文件`libHI3.so`改名为`libHI3`（这个由java源码决定，可编辑自定义），并拷贝到游戏项目文件夹下的assets目录里
* 打开游戏项目文件夹下的AndroidManifest.xml，找到`<application android:appComponentFactory="androidx.core.app.CoreComponentFactory" ... android:name="com.combosdk.openapi.ComboApplication" ...>`  记住这个`"com.combosdk.openapi.ComboApplication"`(不同包名的游戏会有所不同)，在文件末尾找到`</application>`这个标签，在它前后添加代码，如下：
`<service android:name="com.android.archer.support" android:enabled="true" android:exported="false" android:stopWithTask="true"/>
    </application>
	<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>` 保存修改
* 打开游戏项目文件夹下的smali目录, 编辑com/combosdk/openapi/ComboApplication.smali文件，找到`constructor <init>()V`这个方法（一般是第一个方法），在`.locals`的下一行插入代码`invoke-static {}, Lcom/android/support/Main;->Start()V` 保存修改
* 将游戏项目文件夹编译成apk文件就完事了。

## 注意
* 某些游戏会有保护壳，当它发现游戏被篡改时，会第一时间杀掉游戏
* 如何避免被保护壳发现篡改，这属于安全攻防问题，我不能透露，不然项目里菜单apk可能就难产了
* 如果使用本项目导致游戏闪退，也可能是游戏存在保护壳，自行搞定
