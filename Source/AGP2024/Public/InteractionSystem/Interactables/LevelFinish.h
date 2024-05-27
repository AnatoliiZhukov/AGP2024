#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/InteractableActor.h"
#include "LevelFinish.generated.h"

/**
 * 
 */
UCLASS()
class AGP2024_API ALevelFinish : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	ALevelFinish();
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Interact(ACharacter* Interactor) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USceneComponent> FinishLocation;
	bool bInteractorIsMoving;
	
	TObjectPtr<ACharacter> RecentInteractor = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> FinishMontage;
};