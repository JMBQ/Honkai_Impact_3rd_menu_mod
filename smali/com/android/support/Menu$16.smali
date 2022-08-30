.class Lcom/android/support/Menu$16;
.super Ljava/lang/Object;
.source "Menu.java"

# interfaces
.implements Landroid/view/View$OnClickListener;


# annotations
.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/android/support/Menu;->RadioButton(Landroid/widget/LinearLayout;ILjava/lang/String;Ljava/lang/String;)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


# instance fields
.field final synthetic this$0:Lcom/android/support/Menu;

.field final synthetic val$Radioo:Landroid/widget/RadioButton;

.field final synthetic val$featNum:I

.field final synthetic val$finalfeatName:Ljava/lang/String;

.field final synthetic val$radioGroup:Landroid/widget/RadioGroup;

.field final synthetic val$radioName:Ljava/lang/String;

.field final synthetic val$textView:Landroid/widget/TextView;


# direct methods
.method constructor <init>(Lcom/android/support/Menu;Landroid/widget/TextView;Ljava/lang/String;Ljava/lang/String;ILandroid/widget/RadioGroup;Landroid/widget/RadioButton;)V
    .locals 0

    .line 939
    iput-object p1, p0, Lcom/android/support/Menu$16;->this$0:Lcom/android/support/Menu;

    iput-object p2, p0, Lcom/android/support/Menu$16;->val$textView:Landroid/widget/TextView;

    iput-object p3, p0, Lcom/android/support/Menu$16;->val$finalfeatName:Ljava/lang/String;

    iput-object p4, p0, Lcom/android/support/Menu$16;->val$radioName:Ljava/lang/String;

    iput p5, p0, Lcom/android/support/Menu$16;->val$featNum:I

    iput-object p6, p0, Lcom/android/support/Menu$16;->val$radioGroup:Landroid/widget/RadioGroup;

    iput-object p7, p0, Lcom/android/support/Menu$16;->val$Radioo:Landroid/widget/RadioButton;

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onClick(Landroid/view/View;)V
    .locals 3

    .line 941
    iget-object p1, p0, Lcom/android/support/Menu$16;->val$textView:Landroid/widget/TextView;

    new-instance v0, Ljava/lang/StringBuilder;

    invoke-direct {v0}, Ljava/lang/StringBuilder;-><init>()V

    iget-object v1, p0, Lcom/android/support/Menu$16;->val$finalfeatName:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    const-string v1, ": <font color=\'"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    iget-object v1, p0, Lcom/android/support/Menu$16;->this$0:Lcom/android/support/Menu;

    iget-object v1, v1, Lcom/android/support/Menu;->NumberTxtColor:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    const-string v1, "\'>"

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    iget-object v1, p0, Lcom/android/support/Menu$16;->val$radioName:Ljava/lang/String;

    invoke-virtual {v0, v1}, Ljava/lang/StringBuilder;->append(Ljava/lang/String;)Ljava/lang/StringBuilder;

    invoke-virtual {v0}, Ljava/lang/StringBuilder;->toString()Ljava/lang/String;

    move-result-object v0

    invoke-static {v0}, Landroid/text/Html;->fromHtml(Ljava/lang/String;)Landroid/text/Spanned;

    move-result-object v0

    invoke-virtual {p1, v0}, Landroid/widget/TextView;->setText(Ljava/lang/CharSequence;)V

    .line 942
    iget-object p1, p0, Lcom/android/support/Menu$16;->val$finalfeatName:Ljava/lang/String;

    iget v0, p0, Lcom/android/support/Menu$16;->val$featNum:I

    iget-object v1, p0, Lcom/android/support/Menu$16;->val$radioGroup:Landroid/widget/RadioGroup;

    iget-object v2, p0, Lcom/android/support/Menu$16;->val$Radioo:Landroid/widget/RadioButton;

    invoke-virtual {v1, v2}, Landroid/widget/RadioGroup;->indexOfChild(Landroid/view/View;)I

    move-result v1

    invoke-static {p1, v0, v1}, Lcom/android/support/Preferences;->changeFeatureInt(Ljava/lang/String;II)V

    return-void
.end method
