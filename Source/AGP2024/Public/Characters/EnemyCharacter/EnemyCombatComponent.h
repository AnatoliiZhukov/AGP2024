#pragma once

#include "CoreMinimal.h"
#include "Characters/CombatComponentBase.h"
#include "EnemyCombatComponent.generated.h"

class AEnemyCharacter;

UCLASS()
class AGP2024_API UEnemyCombatComponent : public UCombatComponentBase
{
	GENERATED_BODY()

public:
	UEnemyCombatComponent();

	virtual void Attack() override;
	virtual void OnDefeated() override;

	UFUNCTION()
	void AttemptAttack(APawn* PawnToAttack);
	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	FVector AimOffset = FVector(0.f, 0.f, 42.f);
	
	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEnemyCharacter* OwningEnemyCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	APawn* TargetPawn = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UAnimInstance* EnemyCharacterMeshAnimInstance = nullptr;
};