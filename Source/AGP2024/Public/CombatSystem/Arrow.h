

#pragma once

#include "CoreMinimal.h"
#include "ArrowPoolInterface.h"
#include "DamageableInterface.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class UPointLightComponent;
class UArrowShooterComponent;
class UProjectileMovementComponent;
class UArrowMovementComponent;
class USphereComponent;

UCLASS()
class AGP2024_API AArrow : public AActor, public IDamageableInterface, public IArrowPoolInterface
{
	GENERATED_BODY()
	
public:	
	AArrow();
	
	virtual void Damage() override;

	virtual void OnPushed() override;
	virtual void OnPulled() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> ArrowCollision;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ArrowMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UPointLightComponent> ArrowLight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ArrowMovementComponent;

	void AssignToShooter(UArrowShooterComponent* NewShooter) {AssignedShooter = NewShooter;}
	
	UFUNCTION()
	UArrowShooterComponent* GetAssignedShooter() const {return AssignedShooter;}
	
protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float ArrowLifespan = 10.f;
	FTimerHandle ArrowLifespanTimerHandle;
	void OnArrowLifespanExpire();
	
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UArrowShooterComponent* AssignedShooter = nullptr;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void PushToArrowPool();
};