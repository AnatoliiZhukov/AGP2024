#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation montages")
	UAnimMontage* AttackMontage = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Animation montages")
	UAnimMontage* BlockMontage = nullptr;

	UFUNCTION()
	void OnAttackInputReceived(); // Attempts to play the AttackMontage

	UFUNCTION()
	void Attack(); // Check for IDamageables in fron of the player, calling Damage() on the first IDamageable hit
	UFUNCTION()
	void Block(); // Plays the BlockMontage
	
	// Called when PlayerCharacter gets hit by a projectile
	void GameOver();
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackCooldown = 1.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRange = 20.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackSweepRadius = 90.0f;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "References")
	APlayerCharacter* OwningPlayerCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UAnimInstance* ArmsMeshAnimInstance = nullptr;
	
	
	// Used on hit to check if the hit actor is visible before calling Damage()
	bool ActorIsVisible(const FVector& CameraLocation, AActor* Actor);
	
	float LastAttackTime = -AttackCooldown;
	bool AttackIsOnCooldown() const;

};