#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/InteractableActor.h"
#include "Lever.generated.h"

class UMoveable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeverStateChanged, bool, bActivated);

UCLASS()
class AGP2024_API ALever : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	ALever();
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLeverStateChanged OnLeverStateChanged;
	
	virtual void Interact(ACharacter* Interactor) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> LeverMesh;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Properties")
	AActor* TargetActor = nullptr;
	UPROPERTY()
	UMoveable* TargetMoveable = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsActivated = false;
};