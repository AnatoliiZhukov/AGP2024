#include "Characters/PlayerCharacter/CombatComponent.h"

#include "Characters/PlayerCharacter/PlayerCharacter.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerCharacter = CastChecked<APlayerCharacter>(GetOwner());
	
	if (OwningPlayerCharacter->ArmsMesh)
	{
		ArmsMeshAnimInstance = OwningPlayerCharacter->ArmsMesh->GetAnimInstance();
		check(ArmsMeshAnimInstance)
	}
}

void UCombatComponent::OnAttackInputReceived()
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

void UCombatComponent::Attack()
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
			if (AActor* HitActor = Hit.GetActor())
			{
				if (IDamageableInterface* HitDamageable = Cast<IDamageableInterface>(HitActor))
				{
					if(ActorIsVisible(CameraLocation, HitActor))
					{
						HitDamageable->Damage();
					}
				}
			}
		}
	}
}

void UCombatComponent::Block()
{
	if(BlockMontage)
	{
		ArmsMeshAnimInstance->Montage_Play(BlockMontage);
	}
}

void UCombatComponent::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Player was killed, game over"))
}

bool UCombatComponent::AttackIsOnCooldown() const
{
	if(const UWorld* World = GetWorld())
	{
		const float TimeSinceLastAttack = World->GetTimeSeconds() - LastAttackTime;
		return TimeSinceLastAttack < AttackCooldown;
	}
	return false;
}

bool UCombatComponent::ActorIsVisible(const FVector& CameraLocation, AActor* Actor)
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
			FHitResult VisibilityCheckHit;
			DrawDebugLine(World, CameraLocation, Corners[i], FColor::Blue, false, 1.0f);
			if (!World->LineTraceSingleByChannel(
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