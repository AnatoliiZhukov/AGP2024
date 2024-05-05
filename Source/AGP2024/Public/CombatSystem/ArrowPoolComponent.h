// Original ObjectPoolComponent: https://github.com/bennystarfighter/UnrealEngine-ObjectPool

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArrowPoolComponent.generated.h"

class AArrow;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UArrowPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UArrowPoolComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ArrowClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 InitialSpawnAmount = 1;

	UPROPERTY(VisibleInstanceOnly)
	TArray<AActor*> InactivePool;

	UPROPERTY(VisibleInstanceOnly)
	TArray<AActor*> ActivePool;

	UFUNCTION(BlueprintCallable, Category="ObjectPool")
	void Push(AActor* ArrowActor, UPARAM(DisplayName = "Success") bool& Success_Out);

	UFUNCTION(BlueprintCallable, Category="ObjectPool")
	void Pull(AActor* & ArrowActor_Out, UPARAM(DisplayName = "Success") bool& Success_Out);

	UFUNCTION(BlueprintInternalUseOnly)
	AActor* SpawnNewArrow();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};