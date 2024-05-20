#include "CombatSystem/LevelManagerWorldSub.h"

void ULevelManagerWorldSub::BroadcastOnLevelEnemyDefeated() const
{
	OnLevelEnemyDefeated.Broadcast();
}

void ULevelManagerWorldSub::StartChangingTimeDilation(float TargetDilation, float SlowDownRate)
{
	TargetTimeDilation = TargetDilation;
	TimeDilationChangeRate = SlowDownRate;
	
	GetWorld()->GetTimerManager().SetTimer(TimeDilationHandle, this, &ULevelManagerWorldSub::ChangeTimeDilation, 0.1f, true, 0.0f);
}

void ULevelManagerWorldSub::ChangeTimeDilation()
{
	// Calculate the new time dilation factor
	float CurrentTimeDilation = GetWorld()->GetWorldSettings()->TimeDilation;
	float NewTimeDilation = FMath::FInterpTo(CurrentTimeDilation, TargetTimeDilation, GetWorld()->GetDeltaSeconds(), TimeDilationChangeRate);

	// Check if the target time dilation is reached
	if (FMath::IsNearlyEqual(NewTimeDilation, TargetTimeDilation, 0.2f))
	{
		NewTimeDilation = TargetTimeDilation;
		GetWorld()->GetTimerManager().ClearTimer(TimeDilationHandle);
	}
	
	GetWorld()->GetWorldSettings()->SetTimeDilation(NewTimeDilation);
}