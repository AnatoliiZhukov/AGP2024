#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInteractionComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UCharacterInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "InteractionProperties")
	float InteractRange = 400.0f;

	void AttemptInteraction();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APlayerCharacter* OwningPlayerCharacter = nullptr;
	
	ECollisionChannel CollisionTraceChannel = ECC_GameTraceChannel1;
	
	UPROPERTY()
	AActor* TargetInteractable = nullptr;
	AActor* GetInteractableInRange() const;
};