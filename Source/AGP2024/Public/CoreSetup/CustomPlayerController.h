// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class APlayerCharacter;
class ACustomHUD;

UCLASS()
class AGP2024_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> PlayerControllerMappingContext = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> PlayerCharacterMappingContext;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TObjectPtr<APlayerCharacter> PossessedCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TObjectPtr<ACustomHUD> HUD;

	void SetupCamera();
};