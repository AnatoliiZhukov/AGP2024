#include "Widgets/HUDWidget.h"

#include "Components/Image.h"

void UHUDWidget::ShowInteractCrosshair(bool bShow)
{
	if(InteractCrosshair)
	{
		InteractCrosshair->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
