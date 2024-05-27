#include "InteractionSystem/Interactables/LevelFinish.h"

#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/BoxComponent.h"

ALevelFinish::ALevelFinish()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FinishLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FinishLocation"));
	RootComponent = FinishLocation;

	InteractionBox->SetupAttachment(FinishLocation);
}

void ALevelFinish::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!bInteractorIsMoving || !RecentInteractor) return;

	if(AController* Controller = RecentInteractor->GetController())
	{
		FVector TargetLocation = GetActorLocation();
		FVector CurrentLocation = RecentInteractor->GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaSeconds, 200.f);

		FRotator TargetRotation = GetActorRotation();
		FRotator CurrentRotation = Controller->GetControlRotation();
		FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaSeconds, 200.f);
		
		if(CurrentLocation.Equals(TargetLocation, 1.f) && CurrentRotation.Equals(TargetRotation, 1.f))
		{
			NewLocation = TargetLocation;
			NewRotation = TargetRotation;
			bInteractorIsMoving = false;
		}
		RecentInteractor->SetActorLocation(NewLocation);
		Controller->SetControlRotation(NewRotation);
	}
}

void ALevelFinish::Interact(ACharacter* Interactor)
{
	Super::Interact(Interactor);

	RecentInteractor = Interactor; bInteractorIsMoving = true;
	
	if(APlayerCharacter* InteractingPlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		InteractingPlayerCharacter->EnableCharacterInput(false);

		InteractingPlayerCharacter->StopJumping();
		
		if(UAnimInstance* AnimInstance = InteractingPlayerCharacter->GetArmsMesh()->GetAnimInstance())
		{
			if(FinishMontage)
			{
				AnimInstance->Montage_Play(FinishMontage);
			}
		}
	}
}