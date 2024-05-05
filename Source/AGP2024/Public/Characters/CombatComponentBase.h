#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UCombatComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponentBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackCooldown = 1.f;
	float LastAttackTime = -AttackCooldown;
	bool AttackIsOnCooldown() const;
};
