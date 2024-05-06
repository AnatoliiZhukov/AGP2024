#include "Characters/PlayerCharacter/PlayerCombatComponent.h"

#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "CombatSystem/Arrow.h"

// Sets default values for this component's properties
UPlayerCombatComponent::UPlayerCombatComponent()
{
	AttackCooldown = 1.5f;
}

void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerCharacter = CastChecked<APlayerCharacter>(GetOwner());
	
	if (OwningPlayerCharacter->ArmsMesh)
	{
		ArmsMeshAnimInstance = OwningPlayerCharacter->ArmsMesh->GetAnimInstance();
		check(ArmsMeshAnimInstance)
	}
}

void UPlayerCombatComponent::OnAttackInputReceived()
{
	// Play the attack montage if it's not on cooldown and no montage is currently playing
	if(!AttackIsOnCooldown() && AttackMontage && !ArmsMeshAnimInstance->Montage_IsPlaying(NULL))
	{
		ArmsMeshAnimInstance->Montage_Play(AttackMontage);

		if(const UWorld* World = GetWorld())
		{
			LastAttackTime = World->GetTimeSeconds();
		}
	}
}

void UPlayerCombatComponent::Attack() const
{
	if(UWorld* World = GetWorld())
	{
		if(AController* OwningController = OwningPlayerCharacter->GetController())
		{
			// Perform sphere sweep
			FVector CameraLocation;
			FRotator CameraRotation;
			OwningController->GetPlayerViewPoint(CameraLocation, CameraRotation);
			FVector Start = CameraLocation + CameraRotation.Vector() * AttackSweepRadius;
			FVector End = Start + CameraRotation.Vector() * AttackRange;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(GetOwner());
		
			FHitResult Hit;
			World->SweepSingleByChannel(
				Hit,
				Start,
				End,
				FQuat::Identity,
				ECC_GameTraceChannel2,
				FCollisionShape::MakeSphere(AttackSweepRadius),
				CollisionParams
			);
			
			// Process sweep result
			if (AActor* HitActor = Hit.GetActor(); IDamageableInterface* HitDamageable = Cast<IDamageableInterface>(HitActor))
			{
				if(ActorIsVisible(CameraLocation, HitActor))
				{
					if(Cast<AArrow>(HitDamageable))
					{
						HitDamageable->Damage();
						Block();
						UE_LOG(LogTemp, Warning, TEXT("Block"))
						return;
					}
					if(BlockMontage && !!ArmsMeshAnimInstance->Montage_IsPlaying(BlockMontage))
					{
						HitDamageable->Damage();
					}
				}
			}
		}
	}
}

void UPlayerCombatComponent::Block() const
{
	if(BlockMontage)
	{
		ArmsMeshAnimInstance->Montage_Play(BlockMontage);
	}
}

bool UPlayerCombatComponent::ActorIsVisible(const FVector& CameraLocation, AActor* Actor) const
{
	if (UWorld* World = GetWorld())
	{
		if(!Actor) return false;
		FBox BoundingBox = Actor->GetComponentsBoundingBox();
		FVector Corners[8];
		BoundingBox.GetVertices(Corners);
		
		// Perform line traces to all corners
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());
		for (int i = 0; i < 8; i++)
		{
			if (FHitResult VisibilityCheckHit; !World->LineTraceSingleByChannel(
				VisibilityCheckHit,
				CameraLocation,
				Corners[i],
				ECC_Visibility,
				CollisionParams))
			{
				return true;
			}
		}
	}
	return false;
}
