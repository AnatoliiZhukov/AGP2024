#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class UBoxComponent;

UCLASS()
class AGP2024_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableActor();
	virtual void Interact() override;

protected:
	// The box the player needs to look at in order to interact with the actor
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UBoxComponent> InteractionBox;
};