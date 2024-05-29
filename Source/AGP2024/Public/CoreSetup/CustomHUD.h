// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

class UEndScreen;
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
	UEndScreen* GetEndScreen() const {return EndScreen;}
	
	UFUNCTION()
	void SetInputModeGameOnly() const;
	UFUNCTION()
	void SetInputModeGameAndUI(const bool ShowMouseCursor) const;
	UFUNCTION()
	void SetInputModeUIOnly() const;
	UFUNCTION()
	void CenterMouseCursor() const;

	UFUNCTION(BlueprintCallable)
	void ShowEndScreen(bool Success, const FText& Text) const;
	
	UFUNCTION()
	void TogglePauseMenu();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UHUDWidget> HUDWidget;
	void CreateAndShowHUDWidget();
	
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UEndScreen> EndScreenClass;
	UPROPERTY()
	TObjectPtr<UEndScreen> EndScreen;
	void CreateAndCollapseEndScreen();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> PauseMenuClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenu;
	void CreateAndCollapsePauseMenu();
	bool bPauseMenuOpen = false;
};