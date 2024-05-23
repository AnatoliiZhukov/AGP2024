// Copyright:       Copyright (C) 2022 Doğa Can Yanıkoğlu

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CustomCameraManager.generated.h"

class APlayerCharacter;

UCLASS(Blueprintable, BlueprintType)
class AGP2024_API ACustomCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ACustomCameraManager();

	UPROPERTY(EditAnywhere, Category = "Camera")
	float FirstPersonFOV = 103.0f;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void OnPossess(APlayerCharacter* NewCharacter);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<APlayerCharacter> ControlledCharacter = nullptr;
	
protected:
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	static FVector CalculateAxisIndependentLag(
		FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeeds, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	bool CustomCameraBehavior(float DeltaTime, FVector& Location, FRotator& Rotation, float& FOV);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	FVector RootLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	FTransform SmoothedPivotTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	FVector PivotLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	FVector TargetCameraLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	FRotator TargetCameraRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCameraUsesControlRotation = false;
};
