#include "Characters/CombatComponentBase.h"

UCombatComponentBase::UCombatComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponentBase::BeginPlay()
{
	Super::BeginPlay();

	LastAttackTime = -AttackCooldown;
}

void UCombatComponentBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Character is attacking"))
}

void UCombatComponentBase::OnDefeated()
{
	UE_LOG(LogTemp, Warning, TEXT("Character defeated"))
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
