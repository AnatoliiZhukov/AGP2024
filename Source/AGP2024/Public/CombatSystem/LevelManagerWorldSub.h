

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelManagerWorldSub.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelEnemyDefeated);

UCLASS()
class AGP2024_API ULevelManagerWorldSub : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelEnemyDefeated OnLevelEnemyDefeated;
	void BroadcastOnLevelEnemyDefeated() const;
	
	UFUNCTION()
	void StartChangingTimeDilation(float TargetDilation, float SlowDownRate);

	UFUNCTION(BlueprintCallable)
	void TryToDamageActor(AActor* Actor);

protected:
	FTimerHandle TimeDilationHandle;
	float TargetTimeDilation;
	float TimeDilationChangeRate;
	void ChangeTimeDilation();
};