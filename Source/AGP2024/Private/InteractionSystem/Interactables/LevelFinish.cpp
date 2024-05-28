#include "InteractionSystem/Interactables/LevelFinish.h"

#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "CoreSetup/CustomHUD.h"

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
		const FVector TargetLocation = GetActorLocation();
		const FVector CurrentLocation = RecentInteractor->GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaSeconds, 200.f);

		const FRotator TargetRotation = GetActorRotation();
		const FRotator CurrentRotation = Controller->GetControlRotation();
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
	
	if(RecentInteractor) return;
	
	RecentInteractor = Interactor; bInteractorIsMoving = true;
	
	if(APlayerCharacter* InteractingPlayerCharacter = Cast<APlayerCharacter>(Interactor))
	{
		InteractingPlayerCharacter->EnableCharacterInput(false);

		InteractingPlayerCharacter->StopJumping();
		
		if(UAnimInstance* AnimInstance = InteractingPlayerCharacter->GetArmsMesh()->GetAnimInstance())
		{
			if(FinishMontage)
			{
				FOnMontageBlendingOutStarted BlendingOutDelegate;
				BlendingOutDelegate.BindUObject(this, &ALevelFinish::OnMontageBlendingOutStarted);
				AnimInstance->Montage_Play(FinishMontage);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, FinishMontage);
			}
		}
	}
}

void ALevelFinish::OnMontageBlendingOutStarted(UAnimMontage* Montage, bool bInterrupted)
{
	// Stop time and show EndScreen when the animation finishes playing
	
	if(APlayerController* PlayerController = Cast<APlayerController>(RecentInteractor->GetController()))
	{
		if(ACustomHUD* CustomHUD = Cast<ACustomHUD>(PlayerController->GetHUD()))
		{
			CustomHUD->ShowEndScreen(true, FText::FromString("You escaped!"));
		}
	}

	RecentInteractor = nullptr;
}