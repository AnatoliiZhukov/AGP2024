// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSetup/CustomHUD.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/HUDWidget.h"

#pragma region CreatingWidgets

void ACustomHUD::CreateAndShowHUDWidget()
{
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			HUDWidget->ShowInteractCrosshair(false);
		}
	}
}

void ACustomHUD::CreateAndCollapseEndScreen()
{
	if (EndScreenClass)
	{
		EndScreen = CreateWidget<UUserWidget>(GetWorld(), EndScreenClass);
		if (EndScreen)
		{
			EndScreen->AddToViewport();
			EndScreen->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

#pragma endregion

void ACustomHUD::SetInputModeGameOnly() const
{
	FInputModeGameOnly InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->bShowMouseCursor = false;
}

void ACustomHUD::SetInputModeGameAndUI(bool ShowMouseCursor)
{
	FInputModeGameAndUI InputMode;
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->bShowMouseCursor = ShowMouseCursor;

	if(ShowMouseCursor) CenterMouseCursor();
}

void ACustomHUD::SetInputModeUIOnly()
{
	FInputModeUIOnly InputMode;
	APlayerController* PlayerController = GetOwningPlayerController();
	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

	CenterMouseCursor();
}

void ACustomHUD::CenterMouseCursor()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	int32 ScreenWidth, ScreenHeight;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	FVector2D ScreenCenter(ScreenWidth * 0.5f, ScreenHeight * 0.5f);
	PlayerController->SetMouseLocation(ScreenCenter.X, ScreenCenter.Y);
}

void ACustomHUD::SetEndScreenText()
{
	
}

void ACustomHUD::SetEndScreenBackgroundColour()
{
	
}

void ACustomHUD::ShowEndScreen()
{
	if(!EndScreen || EndScreen->GetVisibility() == ESlateVisibility::Visible) return;
	
	SetInputModeUIOnly();
	EndScreen->SetVisibility(ESlateVisibility::Visible);
}

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeGameOnly();

	CreateAndShowHUDWidget();
	CreateAndCollapseEndScreen();
}