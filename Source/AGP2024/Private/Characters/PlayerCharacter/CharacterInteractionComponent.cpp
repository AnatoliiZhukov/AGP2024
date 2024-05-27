#include "Characters/PlayerCharacter/CharacterInteractionComponent.h"

#include "Animation/AnimNode_Inertialization.h"
#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/Image.h"
#include "CoreSetup/CustomHUD.h"
#include "InteractionSystem/InteractableInterface.h"
#include "Widgets/HUDWidget.h"

UCharacterInteractionComponent::UCharacterInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningPlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if(APlayerController* PC = Cast<APlayerController>(OwningPlayerCharacter->GetController()))
	{
		if(ACustomHUD* CHUD = Cast<ACustomHUD>(PC->GetHUD()))
		{
			CustomHUD = CHUD;
		}
	}
}

void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(OwningPlayerCharacter->CharacterInputEnabled())
	{
		TargetInteractable = GetInteractableInRange();
		if(TargetInteractable) CustomHUD->GetHUDWidget()->ShowInteractCrosshair(true);
		else CustomHUD->GetHUDWidget()->ShowInteractCrosshair(false);
		return;
	}

	if(CustomHUD->GetHUDWidget()->InteractCrosshair->IsVisible()) CustomHUD->GetHUDWidget()->ShowInteractCrosshair(false);
}

IInteractableInterface* UCharacterInteractionComponent::GetInteractableInRange() const
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
			if(IInteractableInterface* Interactable = Cast<IInteractableInterface>(Hit.GetActor())) return Interactable;
		}
	}
	return nullptr;
}

void UCharacterInteractionComponent::OnInteractInputReceived()
{
	if(TargetInteractable)
	{
		TargetInteractable->Interact(OwningPlayerCharacter);
	}
}
