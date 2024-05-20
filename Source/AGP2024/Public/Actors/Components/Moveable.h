

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Moveable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP2024_API UMoveable : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveable();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ToggleMoveable();
	UFUNCTION(BlueprintCallable)
	void OffsetMoveable();
	UFUNCTION(BlueprintCallable)
	void ReturnMoveable();
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	FVector MoveOffset = FVector::ZeroVector;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	float MoveSpeed = 100.f;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsMoving = false;
	UPROPERTY(BlueprintReadOnly)
	FVector DefaultLocation = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation = FVector::ZeroVector;
};