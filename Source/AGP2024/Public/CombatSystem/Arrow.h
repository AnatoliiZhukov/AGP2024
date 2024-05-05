

#pragma once

#include "CoreMinimal.h"
#include "ArrowPoolInterface.h"
#include "DamageableInterface.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class UProjectileMovementComponent;
class UArrowMovementComponent;
class USphereComponent;

UCLASS()
class AGP2024_API AArrow : public AActor, public IDamageableInterface, public IArrowPoolInterface
{
	GENERATED_BODY()
	
public:	
	AArrow();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> ArrowCollision;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ArrowMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ArrowMovementComponent;

	virtual void Damage() override;

	virtual void OnPushed() override;
	virtual void OnPulled(UArrowPoolComponent* ArrowPool) override;
	
protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float ArrowLifespan = 2.f;
	FTimerHandle ArrowLifespanTimerHandle;
	void OnArrowLifespanExpire();
	
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UArrowPoolComponent* CurrentArrowPool = nullptr;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);
};