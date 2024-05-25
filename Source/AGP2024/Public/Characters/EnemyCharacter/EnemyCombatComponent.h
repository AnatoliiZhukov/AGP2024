#pragma once

#include "CoreMinimal.h"
#include "Characters/CombatComponentBase.h"
#include "EnemyCombatComponent.generated.h"

class AEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDefeated);

UCLASS()
class AGP2024_API UEnemyCombatComponent : public UCombatComponentBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnEnemyDefeated OnEnemyDefeated;
	
	UEnemyCombatComponent();

	virtual void Attack() override;
	virtual void OnDefeated() override;

	UFUNCTION()
	void AttemptAttack();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	FVector AimOffset = FVector(0.f, 0.f, 42.f);
	
	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEnemyCharacter* OwningEnemyCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UAnimInstance* EnemyCharacterMeshAnimInstance = nullptr;
};