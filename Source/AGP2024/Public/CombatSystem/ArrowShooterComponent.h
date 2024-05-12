

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArrowShooterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UArrowShooterComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UArrowShooterComponent();

	UFUNCTION(BlueprintCallable)
	void ToggleCanShoot() {bCanShoot = !bCanShoot;}
	UFUNCTION(BlueprintCallable)
	void SetShotDirection(FVector NewDirection) {ShotDirection = NewDirection;}
	
	UPROPERTY(EditDefaultsOnly, Category = "ArrowPool")
	int32 InitialSpawnAmount = 10;
	UFUNCTION()
	void Push(AActor* Actor, bool& Success_Out);
	UFUNCTION()
	void Pull(AActor* & Actor_Out, bool& Success_Out);
	
	// Pulls an arrow and changes its rotation and speed
	UFUNCTION(BlueprintCallable)
	void Shoot();
	
	UPROPERTY(EditAnywhere, Category = "Properties")
	float Spread = 1;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float ArrowSpeed = 1000.f;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<AActor> ArrowClass;
	UPROPERTY(EditAnywhere, Category = "Properties")
	FVector ShotDirection = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Properties")
	bool bCanShoot = true;
	
	UPROPERTY()
	TArray<AActor*> InactivePool;
	UPROPERTY()
	TArray<AActor*> ActivePool;
	
	// Spawns a new arrow actor from specified class
	// Called on BeginPlay to create an inactive arrow pool
	// Assigns every new arrow to this shooter
	UFUNCTION()
	AActor* SpawnArrow();
};