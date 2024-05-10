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

	UFUNCTION()
	void AttemptAttack(APawn* PawnToAttack);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AEnemyCharacter* OwningEnemyCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	APawn* TargetPawn = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UAnimInstance* EnemyCharacterMeshAnimInstance = nullptr;
};