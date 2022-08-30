.class Lcom/android/support/Menu$12;
.super Ljava/lang/Object;
.source "Menu.java"

# interfaces
.implements Landroid/widget/AdapterView$OnItemSelectedListener;


# annotations
.annotation system Ldalvik/annotation/EnclosingMethod;
    value = Lcom/android/support/Menu;->Spinner(Landroid/widget/LinearLayout;ILjava/lang/String;Ljava/lang/String;)V
.end annotation

.annotation system Ldalvik/annotation/InnerClass;
    accessFlags = 0x0
    name = null
.end annotation


# instance fields
.field final synthetic this$0:Lcom/android/support/Menu;

.field final synthetic val$featNum:I

.field final synthetic val$spinner:Landroid/widget/Spinner;


# direct methods
.method constructor <init>(Lcom/android/support/Menu;Landroid/widget/Spinner;I)V
    .locals 0

    .line 729
    iput-object p1, p0, Lcom/android/support/Menu$12;->this$0:Lcom/android/support/Menu;

    iput-object p2, p0, Lcom/android/support/Menu$12;->val$spinner:Landroid/widget/Spinner;

    iput p3, p0, Lcom/android/support/Menu$12;->val$featNum:I

    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method


# virtual methods
.method public onItemSelected(Landroid/widget/AdapterView;Landroid/view/View;IJ)V
    .locals 0
    .annotation system Ldalvik/annotation/Signature;
        value = {
            "(",
            "Landroid/widget/AdapterView<",
            "*>;",
            "Landroid/view/View;",
            "IJ)V"
        }
    .end annotation

    .line 732
    iget-object p2, p0, Lcom/android/support/Menu$12;->val$spinner:Landroid/widget/Spinner;

    invoke-virtual {p2}, Landroid/widget/Spinner;->getSelectedItem()Ljava/lang/Object;

    move-result-object p2

    invoke-virtual {p2}, Ljava/lang/Object;->toString()Ljava/lang/String;

    move-result-object p2

    iget p4, p0, Lcom/android/support/Menu$12;->val$featNum:I

    invoke-static {p2, p4, p3}, Lcom/android/support/Preferences;->changeFeatureInt(Ljava/lang/String;II)V

    const/4 p2, 0x0

    .line 733
    invoke-virtual {p1, p2}, Landroid/widget/AdapterView;->getChildAt(I)Landroid/view/View;

    move-result-object p1

    check-cast p1, Landroid/widget/TextView;

    iget-object p2, p0, Lcom/android/support/Menu$12;->this$0:Lcom/android/support/Menu;

    iget p2, p2, Lcom/android/support/Menu;->TEXT_COLOR_2:I

    invoke-virtual {p1, p2}, Landroid/widget/TextView;->setTextColor(I)V

    return-void
.end method

.method public onNothingSelected(Landroid/widget/AdapterView;)V
    .locals 0
    .annotation system Ldalvik/annotation/Signature;
        value = {
            "(",
            "Landroid/widget/AdapterView<",
            "*>;)V"
        }
    .end annotation

    return-void
.end method
