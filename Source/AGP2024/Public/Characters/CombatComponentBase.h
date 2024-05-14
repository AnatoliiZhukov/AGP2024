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
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	bool bAttackContinuously = true;
	
	UFUNCTION()
	virtual void Attack();
	UFUNCTION()
	virtual void OnDefeated();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animation montages")
	UAnimMontage* AttackMontage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackCooldown = 1.f;
	float LastAttackTime = 0.f;
	bool AttackIsOnCooldown() const;
};