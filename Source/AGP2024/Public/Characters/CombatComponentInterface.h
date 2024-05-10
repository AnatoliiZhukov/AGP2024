#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatComponentInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AGP2024_API ICombatComponentInterface
{
	GENERATED_BODY()

public:
	virtual void Attack() = 0;
};
