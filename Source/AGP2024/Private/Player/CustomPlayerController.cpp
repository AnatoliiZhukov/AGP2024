// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CustomPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerCharacter.h"
#include "Player/CustomCameraManager.h"
#include "Player/CustomHUD.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ACustomHUD* CoreSetupHUD = Cast<ACustomHUD>(GetHUD()))
	{
		HUD = CoreSetupHUD;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerControllerMappingContext, 0);
	}
}

void ACustomPlayerController::SetupCamera()
{
	// Call "OnPossess" in Player Camera Manager when possessing a pawn
	ACustomCameraManager* CustomCameraManager = Cast<ACustomCameraManager>(PlayerCameraManager);
	if (PossessedCharacter && CustomCameraManager)
	{
		CustomCameraManager->OnPossess(PossessedCharacter);
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Bind stuff
		
	}
}

void ACustomPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedCharacter = Cast<APlayerCharacter>(InPawn);
	if (!IsRunningDedicatedServer())
	{
		// Servers want to setup camera only in listen servers.
		SetupCamera();
	}
}