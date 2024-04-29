

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemySensingComponent.generated.h"

/**
 * 
 */
UCLASS()
class AGP2024_API UEnemySensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()

protected:
	void OnSeePawn(APawn& Pawn);
};