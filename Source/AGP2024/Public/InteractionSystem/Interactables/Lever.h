#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/InteractableActor.h"
#include "Lever.generated.h"

/**
 * 
 */
UCLASS()
class AGP2024_API ALever : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	ALever();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	virtual void Interact() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> LeverMesh;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Properties")
	AActor* TargetActor = nullptr;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Properties")
	FVector WorldDisplacement = FVector::ZeroVector;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Properties")
	float MoveSpeed = 50.f;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsActivated = false;

	FVector DefaultLocation = FVector::ZeroVector;
	void HandleActorMovement(float DT);
};