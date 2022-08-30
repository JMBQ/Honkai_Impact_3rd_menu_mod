.class Lcom/android/support/Menu$9;
.super Ljava/lang/Object;
.source "Menu.java"

# interfaces
.implements Landroid/view/View$OnClickListener;


# annotations
.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/android/support/Menu;->Button(Landroid/widget/LinearLayout;ILjava/lang/String;)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


# instance fields
.field final synthetic this$0:Lcom/android/support/Menu;

.field final synthetic val$featName:Ljava/lang/String;

.field final synthetic val$featNum:I


# direct methods
.method constructor <init>(Lcom/android/support/Menu;ILjava/lang/String;)V
    .locals 0

    .line 628
    iput-object p1, p0, Lcom/android/support/Menu$9;->this$0:Lcom/android/support/Menu;

    iput p2, p0, Lcom/android/support/Menu$9;->val$featNum:I

    iput-object p3, p0, Lcom/android/support/Menu$9;->val$featName:Ljava/lang/String;

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onClick(Landroid/view/View;)V
    .locals 2

    .line 630
    iget p1, p0, Lcom/android/support/Menu$9;->val$featNum:I

    const/16 v0, -0x64

    if-eq p1, v0, :cond_1

    const/4 v0, -0x6

    if-eq p1, v0, :cond_0

    goto :goto_0

    .line 633
    :cond_0
    iget-object p1, p0, Lcom/android/support/Menu$9;->this$0:Lcom/android/support/Menu;

    iget-object p1, p1, Lcom/android/support/Menu;->scrollView:Landroid/widget/ScrollView;

    iget-object v0, p0, Lcom/android/support/Menu$9;->this$0:Lcom/android/support/Menu;

    iget-object v0, v0, Lcom/android/support/Menu;->mSettings:Landroid/widget/LinearLayout;

    invoke-virtual {p1, v0}, Landroid/widget/ScrollView;->removeView(Landroid/view/View;)V

    .line 634
    iget-object p1, p0, Lcom/android/support/Menu$9;->this$0:Lcom/android/support/Menu;

    iget-object p1, p1, Lcom/android/support/Menu;->scrollView:Landroid/widget/ScrollView;

    iget-object v0, p0, Lcom/android/support/Menu$9;->this$0:Lcom/android/support/Menu;

    iget-object v0, v0, Lcom/android/support/Menu;->mods:Landroid/widget/LinearLayout;

    invoke-virtual {p1, v0}, Landroid/widget/ScrollView;->addView(Landroid/view/View;)V

    goto :goto_0

    .line 637
    :cond_1
    iget-object p1, p0, Lcom/android/support/Menu$9;->this$0:Lcom/android/support/Menu;

    const/4 v0, 0x1

    iput-boolean v0, p1, Lcom/android/support/Menu;->stopChecking:Z

    .line 640
    :goto_0
    iget-object p1, p0, Lcom/android/support/Menu$9;->val$featName:Ljava/lang/String;

    iget v0, p0, Lcom/android/support/Menu$9;->val$featNum:I

    const/4 v1, 0x0

    invoke-static {p1, v0, v1}, Lcom/android/support/Preferences;->changeFeatureInt(Ljava/lang/String;II)V

    return-void
.end method
