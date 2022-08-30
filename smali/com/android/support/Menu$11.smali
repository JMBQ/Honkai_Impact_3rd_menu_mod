.class Lcom/android/support/Menu$11;
.super Ljava/lang/Object;
.source "Menu.java"

# interfaces
.implements Landroid/view/View$OnClickListener;


# annotations
.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/android/support/Menu;->ButtonOnOff(Landroid/widget/LinearLayout;ILjava/lang/String;Z)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


# instance fields
.field isOn:Z

.field final synthetic this$0:Lcom/android/support/Menu;

.field final synthetic val$button:Landroid/widget/Button;

.field final synthetic val$featNum:I

.field final synthetic val$finalIsOn:Z

.field final synthetic val$finalfeatName:Ljava/lang/String;


# direct methods
.method constructor <init>(Lcom/android/support/Menu;ZLjava/lang/String;ILandroid/widget/Button;)V
    .locals 0

    .line 687
    iput-object p1, p0, Lcom/android/support/Menu$11;->this$0:Lcom/android/support/Menu;

    iput-boolean p2, p0, Lcom/android/support/Menu$11;->val$finalIsOn:Z

    iput-object p3, p0, Lcom/android/support/Menu$11;->val$finalfeatName:Ljava/lang/String;

    iput p4, p0, Lcom/android/support/Menu$11;->val$featNum:I

    iput-object p5, p0, Lcom/android/support/Menu$11;->val$button:Landroid/widget/Button;

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    .line 688
    iput-boolean p2, p0, Lcom/android/support/Menu$11;->isOn:Z

    return-void
.end method


# virtual methods
.method public onClick(Landroid/view/View;)V
    .locals 2

    .line 691
    iget-object p1, p0, Lcom/android/support/Menu$11;->val$finalfeatName:Ljava/lang/String;

    iget v0, p0, Lcom/android/support/Menu$11;->val$featNum:I

    iget-boolean v1, p0, Lcom/android/support/Menu$11;->isOn:Z

    invoke-static {p1, v0, v1}, Lcom/android/support/Preferences;->changeFeatureBool(Ljava/lang/String;IZ)I

    .line 693
    iget-boolean p1, p0, Lcom/android/support/Menu$11;->isOn:Z

    if-eqz p1, :cond_0

    .line 694
    iget-object p1, p0, Lcom/android/support/Menu$11;->val$button:Landroid/widget/Button;

    new-instance v0, Ljava/lang/StringBuilder;

    invoke-direct {v0}, Ljava/lang/StringBuilder;-><init>()V

    iget-object v1, p0, Lcom/android/support/Menu$11;->val$finalfeatName:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    const-string v1, ": ON"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    invoke-virtual {v0}, Ljava/lang/StringBuilder;->toString()Ljava/lang/String;

    move-result-object v0

    invoke-static {v0}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v0

    invoke-virtual {p1, v0}, Landroid/widget/Button;->setText(Ljava/lang/CharSequence;)V

    .line 695
    iget-object p1, p0, Lcom/android/support/Menu$11;->val$button:Landroid/widget/Button;

    iget-object v0, p0, Lcom/android/support/Menu$11;->this$0:Lcom/android/support/Menu;

    iget v0, v0, Lcom/android/support/Menu;->BtnON:I

    invoke-virtual {p1, v0}, Landroid/widget/Button;->setBackgroundColor(I)V

    const/4 p1, 0x0

    .line 696
    iput-boolean p1, p0, Lcom/android/support/Menu$11;->isOn:Z

    goto :goto_0

    .line 698
    :cond_0
    iget-object p1, p0, Lcom/android/support/Menu$11;->val$button:Landroid/widget/Button;

    new-instance v0, Ljava/lang/StringBuilder;

    invoke-direct {v0}, Ljava/lang/StringBuilder;-><init>()V

    iget-object v1, p0, Lcom/android/support/Menu$11;->val$finalfeatName:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    const-string v1, ": OFF"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    invoke-virtual {v0}, Ljava/lang/StringBuilder;->toString()Ljava/lang/String;

    move-result-object v0

    invoke-static {v0}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v0

    invoke-virtual {p1, v0}, Landroid/widget/Button;->setText(Ljava/lang/CharSequence;)V

    .line 699
    iget-object p1, p0, Lcom/android/support/Menu$11;->val$button:Landroid/widget/Button;

    iget-object v0, p0, Lcom/android/support/Menu$11;->this$0:Lcom/android/support/Menu;

    iget v0, v0, Lcom/android/support/Menu;->BtnOFF:I

    invoke-virtual {p1, v0}, Landroid/widget/Button;->setBackgroundColor(I)V

    const/4 p1, 0x1

    .line 700
    iput-boolean p1, p0, Lcom/android/support/Menu$11;->isOn:Z

    :goto_0
    return-void
.end method
