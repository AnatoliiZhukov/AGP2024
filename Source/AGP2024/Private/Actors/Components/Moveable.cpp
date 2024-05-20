


#include "Actors/Components/Moveable.h"

UMoveable::UMoveable()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMoveable::BeginPlay()
{
	Super::BeginPlay();

	if(AActor* Owner = GetOwner()) DefaultLocation = GetOwner()->GetActorLocation();
	TargetLocation = DefaultLocation;
}

void UMoveable::ToggleMoveable()
{
	TargetLocation = TargetLocation == DefaultLocation ? TargetLocation + MoveOffset : DefaultLocation;
	if(!bIsMoving) bIsMoving = true;
}

void UMoveable::OffsetMoveable()
{
	TargetLocation = DefaultLocation + MoveOffset;
	if(!bIsMoving) bIsMoving = true;
}

void UMoveable::ReturnMoveable()
{
	TargetLocation = DefaultLocation;
	if(!bIsMoving) bIsMoving = true;
}

void UMoveable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bIsMoving) return;

	if(AActor* Owner = GetOwner())
	{
		FVector CurrentLocation = Owner->GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		Owner->SetActorLocation(NewLocation);
		
		if(NewLocation == TargetLocation) bIsMoving = false;
	}
}