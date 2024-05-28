

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndScreen.generated.h"

class UTextBlock;
class UBorder;
/**
 * 
 */
UCLASS()
class AGP2024_API UEndScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetBackgroundColor(bool Success) const;
	
	UFUNCTION()
	void SetText(const FText& NewText) const;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* EndScreenBackground;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* EndScreenText;

	UPROPERTY(EditAnywhere, Category = "BackgroundColours")
	FLinearColor FailColour = FLinearColor(1.f, 0.f, 0.f, 0.2f);
	UPROPERTY(EditAnywhere, Category = "BackgroundColours")
	FLinearColor SuccessColour = FLinearColor(0.f, 1.f, 0.f, 0.2f);
};