#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCustomCharacterMovement;
class UCharacterInteractionComponent;
class UInputAction;
class UInputMappingContext;

const FName NAME_CameraBone(TEXT("camera"));

UCLASS()
class AGP2024_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	// Getters
	TObjectPtr<USkeletalMeshComponent> GetArmsMesh() const { return ArmsMesh; }
	FVector GetCameraTargetLocation() const { return GetArmsMesh()->GetSocketLocation(NAME_CameraBone); }
	FRotator GetCameraTargetRotation() const { return GetArmsMesh()->GetSocketRotation(NAME_CameraBone); }
	
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCustomCharacterMovement> CustomCharacterMovement;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> ArmsMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCharacterInteractionComponent> CharacterInteractionComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputMappingContext* PlayerCharacterMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputAction* CrouchAction;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputAction* SprintAction;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInput", meta=(AllowPrivateAccess=true))
	UInputAction* InteractAction;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};