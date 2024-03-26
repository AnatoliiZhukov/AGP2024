// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CharacterInputManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Player/CustomCharacterMovement.h"

UCharacterInputManager::UCharacterInputManager()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UCharacterInputManager::SetupCharacterInput(UInputComponent* PlayerInputComponent, const APlayerController* PlayerController)
{
	// Add mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerCharacterMappingContext, 0);
	}
	
	// Bind functions to input actions
	if (UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UCustomCharacterMovement* CustomCharacterMovement =
			GetOwner()->GetComponentByClass<UCustomCharacterMovement>();
		check(CustomCharacterMovement);
		
		EnhancedInputComponent->BindAction(
			MoveAction,
			ETriggerEvent::Triggered,
			CustomCharacterMovement,
			&UCustomCharacterMovement::OnMoveInputReceived);
		
		EnhancedInputComponent->BindAction(
			LookAction,
			ETriggerEvent::Triggered,
			CustomCharacterMovement,
			&UCustomCharacterMovement::OnLookInputReceived);

		EnhancedInputComponent->BindAction(
			JumpAction,
			ETriggerEvent::Triggered,
			CustomCharacterMovement,
			&UCustomCharacterMovement::OnJumpInputReceived);

		EnhancedInputComponent->BindAction(
			CrouchAction,
			ETriggerEvent::Triggered,
			CustomCharacterMovement,
			&UCustomCharacterMovement::OnCrouchInputReceived);

		EnhancedInputComponent->BindAction(
			SprintAction,
			ETriggerEvent::Triggered,
			CustomCharacterMovement,
			&UCustomCharacterMovement::OnSprintInputReceived);
	}
}