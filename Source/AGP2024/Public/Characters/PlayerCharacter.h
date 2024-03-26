// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"

#include "PlayerCharacter.generated.h"

class UCustomCharacterMovement;
class UCharacterInputManager;

const FName NAME_CameraBone(TEXT("camera"));

UCLASS()
class AGP2024_API APlayerCharacter : public ACharacterBase
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
	TObjectPtr<USkeletalMeshComponent> ArmsMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCharacterInputManager> CharacterInputManager;

private:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
