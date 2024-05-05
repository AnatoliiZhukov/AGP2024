#pragma once

#include "CoreMinimal.h"
#include "Characters/CombatComponentBase.h"
#include "PlayerCombatComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UPlayerCombatComponent : public UCombatComponentBase
{
	GENERATED_BODY()

public:	
	UPlayerCombatComponent();

	UFUNCTION()
	void OnAttackInputReceived(); // Attempts to play the AttackMontage

	UFUNCTION()
	void Attack() const; // Tries to find an IDamageable in front of the player and call Damage() on it
	UFUNCTION()
	void Block() const; // Plays the BlockMontage
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation montages")
	UAnimMontage* AttackMontage = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Animation montages")
	UAnimMontage* BlockMontage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRange = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackSweepRadius = 40.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "References")
	APlayerCharacter* OwningPlayerCharacter = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UAnimInstance* ArmsMeshAnimInstance = nullptr;
	
	// Used on hit to check if the hit actor is visible before calling Damage()
	bool ActorIsVisible(const FVector& CameraLocation, AActor* Actor) const;
};