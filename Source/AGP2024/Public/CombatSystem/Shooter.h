

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shooter.generated.h"

class UArrowPoolComponent;

UCLASS()
class AGP2024_API AShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	AShooter();
	virtual void Tick(float DeltaTime) override;

	void SetIsEnabled(bool NewIsEnabled);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UArrowPoolComponent> ShooterArrowPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEnabled = false;
};
