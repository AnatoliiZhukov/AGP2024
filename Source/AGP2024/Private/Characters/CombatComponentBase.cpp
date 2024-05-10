#include "Characters/CombatComponentBase.h"

UCombatComponentBase::UCombatComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponentBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attacking"))
}

bool UCombatComponentBase::AttackIsOnCooldown() const
{
	if(const UWorld* World = GetWorld())
	{
		const float TimeSinceLastAttack = World->GetTimeSeconds() - LastAttackTime;
		return TimeSinceLastAttack < AttackCooldown;
	}
	return false;
}
