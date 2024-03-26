// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CustomCharacterMovement.h"

#include "InputActionValue.h"
#include "Characters/PlayerCharacter.h"

UCustomCharacterMovement::UCustomCharacterMovement()
{
	GetNavAgentPropertiesRef().bCanCrouch = true;
}

void UCustomCharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	check(OwningPlayerCharacter);
}

void UCustomCharacterMovement::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation,
                                                 const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
	
	HandleMeshRotation();
	HandleJumping();
	HandleMeshHeight(DeltaSeconds);
	HandleSprinting();
}

void UCustomCharacterMovement::ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration)
{
	// Only apply friction if jump is not queued
	if(bJumpQueued) {return;}

	Super::ApplyVelocityBraking(DeltaTime, Friction, BrakingDeceleration);
}

void UCustomCharacterMovement::HandleMeshRotation()
{
	const FRotator PawnViewRotation = OwningPlayerCharacter->GetViewRotation();
	if (!PawnViewRotation.Equals(OwningPlayerCharacter->GetArmsMesh()->GetComponentRotation()))
	{
		OwningPlayerCharacter->GetArmsMesh()->SetWorldRotation(PawnViewRotation);
	}
}

void UCustomCharacterMovement::HandleJumping()
{
	if(!IsCrouching() && bJumpQueued && IsMovingOnGround())
	{
		OwningPlayerCharacter->Jump();
		bJumpQueued = false;
	}
}

void UCustomCharacterMovement::HandleMeshHeight(float DeltaSeconds)
{

	// Determine the target height based on whether the character is crouching or not
	const float TargetHeight = IsCrouching() ? CrouchHeight : StandingHeight;
	
	const FVector CurrentLocation = OwningPlayerCharacter->GetArmsMesh()->GetRelativeLocation();
	const float CurrentHeight = CurrentLocation.Z;
	// Check if the mesh is already at the target height
	if (CurrentHeight == TargetHeight) {return;}
	FVector NewLocation = CurrentLocation;
	if (!FMath::IsNearlyEqual(CurrentHeight, TargetHeight, 0.5f))
	{
		//Interpolate the Z value
		NewLocation.Z = FMath::FInterpTo(CurrentHeight, TargetHeight, DeltaSeconds, CrouchSpeed);
	}
	else
	{
		NewLocation.Z = TargetHeight;
	}
	OwningPlayerCharacter->GetArmsMesh()->SetRelativeLocation(NewLocation);
}

void UCustomCharacterMovement::HandleSprinting()
{
	bWantsToSprint ? MaxWalkSpeed = SprintSpeed : MaxWalkSpeed = WalkSpeed;
}

#pragma region PlayerInput

void UCustomCharacterMovement::OnMoveInputReceived(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveInput = InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	OwningPlayerCharacter->AddMovementInput(ForwardDirection, MoveInput.Y);
	OwningPlayerCharacter->AddMovementInput(RightDirection, MoveInput.X);

	if ((bIsMovingForward && MoveInput.Y <= 0) || (!bIsMovingForward && MoveInput.Y > 0))
	{
		bIsMovingForward = !bIsMovingForward;
	}
}

void UCustomCharacterMovement::OnLookInputReceived(const FInputActionValue& InputActionValue)
{
	const FVector2D LookInput = InputActionValue.Get<FVector2D>() * LookSens;

	OwningPlayerCharacter->AddControllerYawInput(LookInput.X);
	OwningPlayerCharacter->AddControllerPitchInput(LookInput.Y);
}

void UCustomCharacterMovement::OnJumpInputReceived(const FInputActionValue& InputActionValue)
{
	const bool JumpInput = InputActionValue.Get<bool>();
	
	if(JumpInput && !bJumpQueued)
	{
		bJumpQueued = true;
		if(IsCrouching()) {bWantsToCrouch = false;}
	}
	else if(!JumpInput && bJumpQueued)
	{
		bJumpQueued = false;
		if(IsCrouching() && bToggleCrouch) {bWantsToCrouch = true;}
	}
}

void UCustomCharacterMovement::OnCrouchInputReceived(const FInputActionValue& InputActionValue)
{
	const bool CrouchInput = InputActionValue.Get<bool>();
	
	// Hold/toggle crouch logic
	if(!bToggleCrouch)
	{
		if(CrouchInput) {OwningPlayerCharacter->Crouch();}
		else {OwningPlayerCharacter->UnCrouch();}
	}
	else if (CrouchInput)
	{
		if(IsCrouching()) {OwningPlayerCharacter->UnCrouch();}
		else {OwningPlayerCharacter->UnCrouch();}
	}
	//  Dash logic
	if(bCanDashOnCrouch && CrouchInput && !IsMovingOnGround())
	{
		OwningPlayerCharacter->LaunchCharacter(DashVelocity, false, true);
	}
}

void UCustomCharacterMovement::OnSprintInputReceived(const FInputActionValue& InputActionValue)
{
	const bool SprintInput = InputActionValue.Get<bool>();
	bWantsToSprint = bIsMovingForward && SprintInput;
}

#pragma endregion