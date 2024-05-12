#include "InteractionSystem/Interactables/Lever.h"

#include "Components/BoxComponent.h"

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = true;
	
	LeverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LevelMesh"));
	RootComponent = LeverMesh;

	InteractionBox->SetupAttachment(LeverMesh);
}

void ALever::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleActorMovement(DeltaSeconds);
}

void ALever::BeginPlay()
{
	Super::BeginPlay();

	if(TargetActor) DefaultLocation = TargetActor->GetActorLocation();
	else {UE_LOG(LogTemp, Error, TEXT("A lever in the world has its TargetActor not set, interacting with it won't do anything"))}
}

void ALever::Interact()
{
	Super::Interact();

	bIsActivated = !bIsActivated;
}

void ALever::HandleActorMovement(float DeltaSeconds)
{
	if(!TargetActor) return;
	
	// Set actor target height
	const FVector TargetLocation = bIsActivated ? DefaultLocation + WorldDisplacement : DefaultLocation;
	
	// Check if the actor is already at target location
	const FVector CurrentLocation = TargetActor->GetActorLocation();
	if (CurrentLocation == TargetLocation) {return;}

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaSeconds, MoveSpeed);
	TargetActor->SetActorLocation(NewLocation);
}
