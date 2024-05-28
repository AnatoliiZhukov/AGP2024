#include "CoreSetup/CustomPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "CoreSetup/CustomCameraManager.h"
#include "CoreSetup/CustomHUD.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ACustomHUD* CustomHUD = Cast<ACustomHUD>(GetHUD()))
	{
		HUD = CustomHUD;
	}
}

void ACustomPlayerController::OnEscInputReceived()
{
	UE_LOG(LogTemp, Warning, TEXT("e"))
	if(HUD) HUD->TogglePauseMenu();
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

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerControllerMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(
			EscAction,
			ETriggerEvent::Triggered,
			this,
			&ACustomPlayerController::OnEscInputReceived);
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