// Copyright:       Copyright (C) 2022 Doğa Can Yanıkoğlu

#include "Player/CustomCameraManager.h"
#include "Characters/PlayerCharacter.h"

ACustomCameraManager::ACustomCameraManager()
{
}

void ACustomCameraManager::OnPossess(APlayerCharacter* NewCharacter)
{
    check(NewCharacter);
    ControlledCharacter = NewCharacter;

    // Initial position
    const FVector& TargetLoc = ControlledCharacter->GetCameraTargetLocation();
    SetActorLocation(TargetLoc);
}

void ACustomCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
    if (OutVT.Target)
    {
        FVector OutLocation;
        FRotator OutRotation;
        float OutFOV;

        if (OutVT.Target->IsA<APlayerCharacter>())
        {
            if (CustomCameraBehavior(DeltaTime, OutLocation, OutRotation, OutFOV))
            {
                OutVT.POV.Location = OutLocation;
                OutVT.POV.Rotation = OutRotation;
                OutVT.POV.FOV = OutFOV;
            }
            else
            {
                OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
            }
        }
        else
        {
            OutVT.Target->CalcCamera(DeltaTime, OutVT.POV);
        }
    }
}

bool ACustomCameraManager::CustomCameraBehavior(float DeltaTime, FVector& Location, FRotator& Rotation, float& FOV)
{
    if (!ControlledCharacter)
    {
        return false;
    }

    // Set new rotation
    if(bCameraUsesControlRotation)
    {
        const FRotator& ControlRotation = ControlledCharacter->GetControlRotation();
        Rotation = ControlRotation;
    }
    else
    {
        const FRotator& TargetRot = ControlledCharacter->GetCameraTargetRotation();
        Rotation = TargetRot;
    }

    // Set new location
    const FVector& TargetLoc = ControlledCharacter->GetCameraTargetLocation();
    Location = TargetLoc;
    
    FOV = FirstPersonFOV;

    return true;
}

FVector ACustomCameraManager::CalculateAxisIndependentLag(FVector CurrentLocation, FVector TargetLocation, FRotator CameraRotation, FVector LagSpeeds, float DeltaTime)
{
    return FVector::ZeroVector;
}