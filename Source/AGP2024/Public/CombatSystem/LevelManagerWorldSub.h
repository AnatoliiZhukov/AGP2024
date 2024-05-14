

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelManagerWorldSub.generated.h"

/**
 * 
 */
UCLASS()
class AGP2024_API ULevelManagerWorldSub : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void StartChangingTimeDilation(float TargetDilation, float SlowDownRate);

protected:
	FTimerHandle TimeDilationHandle;
	float TargetTimeDilation;
	float TimeDilationChangeRate;
	void ChangeTimeDilation();
};