#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/DamageableInterface.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UEnemySensingComponent;

UCLASS()
class AGP2024_API AEnemyCharacter : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Damage() override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UEnemySensingComponent> EnemySensingComponent;
};
