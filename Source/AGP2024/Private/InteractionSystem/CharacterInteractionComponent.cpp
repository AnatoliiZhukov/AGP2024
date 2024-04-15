#include "InteractionSystem/CharacterInteractionComponent.h"

#include "Characters/CharacterBase.h"
#include "InteractionSystem/InteractableInterface.h"

UCharacterInteractionComponent::UCharacterInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningCharacter = Cast<ACharacterBase>(GetOwner());
}

void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TargetInteractable = GetInteractableInRange();
}

AActor* UCharacterInteractionComponent::GetInteractableInRange() const
{
	if(!GetWorld() || !OwningCharacter) return nullptr;

	if(AController* OwningController = OwningCharacter->GetController())
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
