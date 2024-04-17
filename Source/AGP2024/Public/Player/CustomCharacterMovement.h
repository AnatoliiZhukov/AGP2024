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
	void OnRunInputReceived(const FInputActionValue& InputActionValue);

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	UPROPERTY(EditDefaultsOnly, Category = "Properties | Look")
	float LookSensitivity = 0.5f;
	
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Sprint")
	float RunSpeed = 900.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Properties | Sprint")
	float WalkSpeed = 600.0f;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetWalkSpeed() const {return WalkSpeed;}
	
	UPROPERTY(BlueprintReadOnly)
	bool bWantsToRun = false;
	
protected:
	virtual void BeginPlay() override;

	virtual void ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration) override;

	bool bIsMovingForward;
	bool bJumpQueued = false;
	
private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> OwningPlayerCharacter = nullptr;
	
	void HandleMeshRotation();
	void HandleJumping();
	void HandleMeshHeight(float DeltaSeconds);
	void HandleRunning();
};
