.class public Lcom/android/support/MainActivity;
.super Landroid/app/Activity;
.source "MainActivity.java"


# instance fields
.field public GameActivity:Ljava/lang/String;

.field public hasLaunched:Z


# direct methods
.method public constructor <init>()V
    .locals 1

    .line 11
    invoke-direct {p0}, Landroid/app/Activity;-><init>()V

    const-string v0, "com.miHoYo.overridenativeactivity.OverrideNativeActivity"

    .line 14
    iput-object v0, p0, Lcom/android/support/MainActivity;->GameActivity:Ljava/lang/String;

    const/4 v0, 0x0

    .line 15
    iput-boolean v0, p0, Lcom/android/support/MainActivity;->hasLaunched:Z

    return-void
.end method


# virtual methods
.method protected onCreate(Landroid/os/Bundle;)V
    .locals 1

    .line 20
    invoke-super {p0, p1}, Landroid/app/Activity;->onCreate(Landroid/os/Bundle;)V

    .line 60
    iget-boolean p1, p0, Lcom/android/support/MainActivity;->hasLaunched:Z

    if-nez p1, :cond_0

    const/4 p1, 0x1

    .line 63
    :try_start_0
    iput-boolean p1, p0, Lcom/android/support/MainActivity;->hasLaunched:Z

    .line 65
    new-instance p1, Landroid/content/Intent;

    iget-object v0, p0, Lcom/android/support/MainActivity;->GameActivity:Ljava/lang/String;

    invoke-static {v0}, Ljava/lang/Class;->forName(Ljava/lang/String;)Ljava/lang/Class;

    move-result-object v0

    invoke-direct {p1, p0, v0}, Landroid/content/Intent;-><init>(Landroid/content/Context;Ljava/lang/Class;)V

    invoke-virtual {p0, p1}, Lcom/android/support/MainActivity;->startActivity(Landroid/content/Intent;)V

    .line 66
    invoke-static {p0}, Lcom/android/support/Main;->Start(Landroid/content/Context;)V
    :try_end_0
    .catch Ljava/lang/ClassNotFoundException; {:try_start_0 .. :try_end_0} :catch_0
    .catch Ljava/io/IOException; {:try_start_0 .. :try_end_0} :catch_0
    .catch Ljava/lang/InterruptedException; {:try_start_0 .. :try_end_0} :catch_0

    return-void

    :catch_0
    const-string p1, "Mod_menu"

    const-string v0, "Error. Game\'s main activity does not exist"

    .line 69
    invoke-static {p1, v0}, Landroid/util/Log;->e(Ljava/lang/String;Ljava/lang/String;)I

    .line 78
    :cond_0
    :try_start_1
    invoke-static {p0}, Lcom/android/support/Main;->Start(Landroid/content/Context;)V
    :try_end_1
    .catch Ljava/io/IOException; {:try_start_1 .. :try_end_1} :catch_2
    .catch Ljava/lang/InterruptedException; {:try_start_1 .. :try_end_1} :catch_1

    goto :goto_1

    :catch_1
    move-exception p1

    goto :goto_0

    :catch_2
    move-exception p1

    .line 80
    :goto_0
    invoke-virtual {p1}, Ljava/lang/Exception;->printStackTrace()V

    :goto_1
    return-void
.end method
