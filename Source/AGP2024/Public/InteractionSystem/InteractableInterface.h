#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AGP2024_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Interact(ACharacter* Interactor) = 0;
};
