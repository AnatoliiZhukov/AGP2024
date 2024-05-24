#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class AGP2024_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowInteractCrosshair(bool bShow);

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UImage> InteractCrosshair;
};
