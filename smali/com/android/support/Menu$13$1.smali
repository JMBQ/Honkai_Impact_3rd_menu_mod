.class Lcom/android/support/Menu$13$1;
.super Ljava/lang/Object;
.source "Menu.java"

# interfaces
.implements Landroid/view/View$OnFocusChangeListener;


# annotations
.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/android/support/Menu$13;->onClick(Landroid/view/View;)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


# instance fields
.field final synthetic this$1:Lcom/android/support/Menu$13;


# direct methods
.method constructor <init>(Lcom/android/support/Menu$13;)V
    .locals 0

    .line 768
    iput-object p1, p0, Lcom/android/support/Menu$13$1;->this$1:Lcom/android/support/Menu$13;

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onFocusChange(Landroid/view/View;Z)V
    .locals 1

    .line 771
    iget-object p1, p0, Lcom/android/support/Menu$13$1;->this$1:Lcom/android/support/Menu$13;

    iget-object p1, p1, Lcom/android/support/Menu$13;->this$0:Lcom/android/support/Menu;

    iget-object p1, p1, Lcom/android/support/Menu;->getContext:Landroid/content/Context;

    iget-object v0, p0, Lcom/android/support/Menu$13$1;->this$1:Lcom/android/support/Menu$13;

    iget-object v0, v0, Lcom/android/support/Menu$13;->this$0:Lcom/android/support/Menu;

    iget-object v0, v0, Lcom/android/support/Menu;->getContext:Landroid/content/Context;

    const-string v0, "input_method"

    invoke-virtual {p1, v0}, Landroid/content/Context;->getSystemService(Ljava/lang/String;)Ljava/lang/Object;

    move-result-object p1

    check-cast p1, Landroid/view/inputmethod/InputMethodManager;

    const/4 v0, 0x1

    if-eqz p2, :cond_0

    const/4 p2, 0x2

    .line 773
    invoke-virtual {p1, p2, v0}, Landroid/view/inputmethod/InputMethodManager;->toggleSoftInput(II)V

    goto :goto_0

    :cond_0
    const/4 p2, 0x0

    .line 775
    invoke-virtual {p1, v0, p2}, Landroid/view/inputmethod/InputMethodManager;->toggleSoftInput(II)V

    :goto_0
    return-void
.end method
