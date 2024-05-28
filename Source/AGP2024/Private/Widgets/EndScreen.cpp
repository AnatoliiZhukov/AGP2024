#include "Widgets/EndScreen.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

void UEndScreen::SetBackgroundColor(const bool Success) const
{
	if(Success) EndScreenBackground->SetBrushColor(SuccessColour);
	else EndScreenBackground->SetBrushColor(FailColour);
}

void UEndScreen::SetText(const FText& NewText) const
{
	EndScreenText->SetText(NewText);
}
