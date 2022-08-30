.class Lcom/android/support/Menu$13$2;
.super Ljava/lang/Object;
.source "Menu.java"

# interfaces
.implements Landroid/content/DialogInterface$OnClickListener;


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

.field final synthetic val$editText:Landroid/widget/EditText;


# direct methods
.method constructor <init>(Lcom/android/support/Menu$13;Landroid/widget/EditText;)V
    .locals 0

    .line 788
    iput-object p1, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iput-object p2, p0, Lcom/android/support/Menu$13$2;->val$editText:Landroid/widget/EditText;

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onClick(Landroid/content/DialogInterface;I)V
    .locals 2

    .line 792
    :try_start_0
    iget-object p1, p0, Lcom/android/support/Menu$13$2;->val$editText:Landroid/widget/EditText;

    invoke-virtual {p1}, Landroid/widget/EditText;->getText()Landroid/text/Editable;

    move-result-object p1

    invoke-virtual {p1}, Ljava/lang/Object;->toString()Ljava/lang/String;

    move-result-object p1

    invoke-static {p1}, Landroid/text/TextUtils;->isEmpty(Ljava/lang/CharSequence;)Z

    move-result p1

    if-eqz p1, :cond_0

    const-string p1, "0"

    goto :goto_0

    :cond_0
    iget-object p1, p0, Lcom/android/support/Menu$13$2;->val$editText:Landroid/widget/EditText;

    invoke-virtual {p1}, Landroid/widget/EditText;->getText()Landroid/text/Editable;

    move-result-object p1

    invoke-virtual {p1}, Ljava/lang/Object;->toString()Ljava/lang/String;

    move-result-object p1

    :goto_0
    invoke-static {p1}, Ljava/lang/Integer;->parseInt(Ljava/lang/String;)I

    move-result p1

    .line 793
    iget-object p2, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget p2, p2, Lcom/android/support/Menu$13;->val$maxValue:I

    if-eqz p2, :cond_2

    iget-object p2, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget p2, p2, Lcom/android/support/Menu$13;->val$maxValue:I

    if-lt p1, p2, :cond_2

    .line 794
    iget-object p1, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget p1, p1, Lcom/android/support/Menu$13;->val$maxValue:I
    :try_end_0
    .catch Ljava/lang/NumberFormatException; {:try_start_0 .. :try_end_0} :catch_0

    goto :goto_1

    :catch_0
    nop

    .line 796
    iget-object p1, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget p1, p1, Lcom/android/support/Menu$13;->val$maxValue:I

    if-eqz p1, :cond_1

    .line 797
    iget-object p1, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget p1, p1, Lcom/android/support/Menu$13;->val$maxValue:I

    goto :goto_1

    :cond_1
    const p1, 0x7ffffff8

    .line 802
    :cond_2
    :goto_1
    iget-object p2, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget-object p2, p2, Lcom/android/support/Menu$13;->val$button:Landroid/widget/Button;

    new-instance v0, Ljava/lang/StringBuilder;

    invoke-direct {v0}, Ljava/lang/StringBuilder;-><init>()V

    iget-object v1, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget-object v1, v1, Lcom/android/support/Menu$13;->val$featName:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    const-string v1, ": <font color=\'"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    iget-object v1, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget-object v1, v1, Lcom/android/support/Menu$13;->this$0:Lcom/android/support/Menu;

    iget-object v1, v1, Lcom/android/support/Menu;->NumberTxtColor:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    const-string v1, "\'>"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    invoke-virtual {v0, p1}, Ljava/lang/StringBuilder;->append(I)Ljava/lang/StringBuilder;

    const-string v1, "</font>"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    invoke-virtual {v0}, Ljava/lang/StringBuilder;->toString()Ljava/lang/String;

    move-result-object v0

    invoke-static {v0}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v0

    invoke-virtual {p2, v0}, Landroid/widget/Button;->setText(Ljava/lang/CharSequence;)V

    .line 803
    iget-object p2, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget-object p2, p2, Lcom/android/support/Menu$13;->val$featName:Ljava/lang/String;

    iget-object v0, p0, Lcom/android/support/Menu$13$2;->this$1:Lcom/android/support/Menu$13;

    iget v0, v0, Lcom/android/support/Menu$13;->val$featNum:I

    invoke-static {p2, v0, p1}, Lcom/android/support/Preferences;->changeFeatureInt(Ljava/lang/String;II)V

    .line 805
    iget-object p1, p0, Lcom/android/support/Menu$13$2;->val$editText:Landroid/widget/EditText;

    const/4 p2, 0x0

    invoke-virtual {p1, p2}, Landroid/widget/EditText;->setFocusable(Z)V

    return-void
.end method
