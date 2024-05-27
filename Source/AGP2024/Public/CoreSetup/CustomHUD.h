// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

class UHUDWidget;
/**
 * 
 */
UCLASS()
class AGP2024_API ACustomHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHUDWidget* GetHUDWidget() const {return HUDWidget;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UUserWidget* GetEndScreen() const {return EndScreen;}
	
	UFUNCTION()
	void SetInputModeGameOnly() const;
	UFUNCTION()
	void SetInputModeGameAndUI(bool ShowMouseCursor);
	UFUNCTION()
	void SetInputModeUIOnly();
	UFUNCTION()
	void CenterMouseCursor();

	UFUNCTION()
	void SetEndScreenText();
	UFUNCTION()
	void SetEndScreenBackgroundColour();
	UFUNCTION()
	void ShowEndScreen();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UHUDWidget> HUDWidget;
	void CreateAndShowHUDWidget();
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> EndScreenClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> EndScreen;
	void CreateAndCollapseEndScreen();

};