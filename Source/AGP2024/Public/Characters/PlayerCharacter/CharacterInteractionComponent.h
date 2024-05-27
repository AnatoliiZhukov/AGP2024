#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInteractionComponent.generated.h"

class IInteractableInterface;
class ACustomHUD;
class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UCharacterInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "InteractionProperties")
	float InteractRange = 200.0f;

	void OnInteractInputReceived();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> OwningPlayerCharacter = nullptr;
	UPROPERTY()
	TObjectPtr<ACustomHUD> CustomHUD = nullptr;
	
	ECollisionChannel CollisionTraceChannel = ECC_GameTraceChannel1;
	
	IInteractableInterface* TargetInteractable = nullptr;
	IInteractableInterface* GetInteractableInRange() const;
};