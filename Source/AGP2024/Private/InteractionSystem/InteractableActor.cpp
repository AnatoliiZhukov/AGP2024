#include "InteractionSystem/InteractableActor.h"

#include "Components/BoxComponent.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Create InteractionBox and set it to ignore everything except InteractTrace
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	
	RootComponent = InteractionBox;
}

void AInteractableActor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction successful"))
}