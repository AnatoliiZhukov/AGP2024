

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelManagerWorldSub.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnyEnemyDefeated);

UCLASS()
class AGP2024_API ULevelManagerWorldSub : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAnyEnemyDefeated OnAnyEnemyDefeated;
	void BroadcastOnAnyEnemyDefeated();
	
	UFUNCTION()
	void StartChangingTimeDilation(float TargetDilation, float SlowDownRate);

	UFUNCTION(BlueprintCallable)
	void TryToDamageActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetEnemiesDefeated() const {return EnemiesDefeated;}

protected:
	FTimerHandle TimeDilationHandle;
	float TargetTimeDilation;
	float TimeDilationChangeRate;
	void ChangeTimeDilation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemiesDefeated = 0;
};