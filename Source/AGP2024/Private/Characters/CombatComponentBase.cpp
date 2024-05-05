#include "Characters/CombatComponentBase.h"

UCombatComponentBase::UCombatComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
	
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