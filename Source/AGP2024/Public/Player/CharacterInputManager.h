// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInputManager.generated.h"

class UInputAction;
class UInputMappingContext;
class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UCharacterInputManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterInputManager();

	void SetupCharacterInput(UInputComponent* PlayerInputComponent, const APlayerController* PlayerController);

private:
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess=true))
	UInputMappingContext* PlayerCharacterMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess=true))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess=true))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess=true))
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess=true))
	UInputAction* CrouchAction;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput", meta=(AllowPrivateAccess=true))
	UInputAction* SprintAction;
};