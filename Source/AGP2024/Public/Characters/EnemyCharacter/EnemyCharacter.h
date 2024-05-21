#pragma once

#include "CoreMinimal.h"
#include "CombatSystem/DamageableInterface.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UArrowShooterComponent;
class UArrowPoolComponent;
class UEnemyCombatComponent;
class UEnemySensingComponent;

UCLASS()
class AGP2024_API AEnemyCharacter : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void Tick(float DeltaSeconds) override;
	virtual void Damage() override;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDefeated = false;

	UFUNCTION(BlueprintCallable)
	UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UEnemySensingComponent> EnemySensingComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UArrowShooterComponent> EnemyShooterComponent;
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSeePawn(APawn *OtherPawn);

	UPROPERTY(EditDefaultsOnly)
	float TimeUntilLosesInterest = 5.0f;
	float LastSeenTime;
	bool IsInterested() const;
	void HandleInterest();

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed = 150.f;
	UPROPERTY()
	APawn* LookAtPawn;
	FRotator DefaultRotation;
	void HandleCharacterRotation(float DT);
};