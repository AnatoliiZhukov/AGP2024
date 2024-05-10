// Original ObjectPoolComponent: https://github.com/bennystarfighter/UnrealEngine-ObjectPool

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArrowPoolInterface.generated.h"

class UArrowPoolComponent;

UINTERFACE(MinimalAPI)
class UArrowPoolInterface : public UInterface
{
	GENERATED_BODY()
};

class AGP2024_API IArrowPoolInterface
{
	GENERATED_BODY()

public:
	virtual void OnPushed() = 0;
	virtual void OnPulled() = 0;
};