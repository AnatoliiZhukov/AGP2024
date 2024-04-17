#include "InteractionSystem/CharacterInteractionComponent.h"
#include "Characters/PlayerCharacter.h"
#include "InteractionSystem/InteractableInterface.h"

UCharacterInteractionComponent::UCharacterInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningPlayerCharacter = Cast<APlayerCharacter>(GetOwner());
}

void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TargetInteractable = GetInteractableInRange();
}

AActor* UCharacterInteractionComponent::GetInteractableInRange() const
{
	if(!GetWorld() || !OwningPlayerCharacter) return nullptr;

	if(AController* OwningController = OwningPlayerCharacter->GetController())
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		OwningController->GetPlayerViewPoint(CameraLocation, CameraRotation);
		FVector Start = CameraLocation;
		FVector End = Start + CameraRotation.Vector() * InteractRange;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		
		if(FHitResult Hit; GetWorld()->LineTraceSingleByChannel(Hit, Start, End, CollisionTraceChannel, CollisionParams))
		{
			return Hit.GetActor();
		}
	}
	return nullptr;
}

void UCharacterInteractionComponent::AttemptInteraction()
{
	if(!TargetInteractable) return;
	
	Cast<IInteractableInterface>(TargetInteractable)->Interact();
}
