#include "InteractionSystem/Interactables/Lever.h"

#include "Actors/Components/Moveable.h"
#include "Components/BoxComponent.h"

ALever::ALever()
{
	PrimaryActorTick.bCanEverTick = false;
	
	LeverMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LevelMesh"));
	RootComponent = LeverMesh;

	InteractionBox->SetupAttachment(LeverMesh);
}

void ALever::BeginPlay()
{
	Super::BeginPlay();
	
	if(TargetActor) TargetMoveable = TargetActor->GetComponentByClass<UMoveable>();
}

void ALever::Interact()
{
	Super::Interact();

	bIsActivated = !bIsActivated;
	OnLeverStateChanged.Broadcast(bIsActivated);

	if(TargetMoveable) TargetMoveable->ToggleMoveable();
}
