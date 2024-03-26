// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovement.generated.h"

class APlayerCharacter;

struct FInputActionValue;

UCLASS()
class AGP2024_API UCustomCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UCustomCharacterMovement();
	
	UFUNCTION(BlueprintCallable)
	void OnMoveInputReceived(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable)
	void OnLookInputReceived(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable)
	void OnJumpInputReceived(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable)
	void OnCrouchInputReceived(const FInputActionValue& InputActionValue);
	UFUNCTION(BlueprintCallable)
	void OnSprintInputReceived(const FInputActionValue& InputActionValue);

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
	
protected:
	virtual void BeginPlay() override;

	virtual void ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration) override;
private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> OwningPlayerCharacter = nullptr;

	bool bIsMovingForward;
	
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Look")
	float LookSens = 0.5f;
	
	bool bJumpQueued = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Crouch")
	bool bToggleCrouch = false;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Crouch")
	float StandingHeight = 78.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Crouch")
	float CrouchHeight = -20.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Crouch")
	float CrouchSpeed = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Crouch")
	bool bCanDashOnCrouch = true;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Crouch")
	FVector DashVelocity = FVector(0, 0, -1000);
	
	bool bWantsToSprint = false;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Sprint")
	float SprintSpeed = 900.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Sprint")
	float WalkSpeed = 600.0f;
	
	void HandleMeshRotation();
	void HandleJumping();
	void HandleMeshHeight(float DeltaSeconds);
	void HandleSprinting();
};
