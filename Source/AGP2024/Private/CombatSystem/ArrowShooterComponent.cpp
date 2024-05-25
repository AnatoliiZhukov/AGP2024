


#include "CombatSystem/ArrowShooterComponent.h"

#include "CombatSystem/Arrow.h"
#include "CombatSystem/ArrowPoolInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/FastReferenceCollector.h"

UArrowShooterComponent::UArrowShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UArrowShooterComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < InitialSpawnAmount; ++i) SpawnArrow();
}

void UArrowShooterComponent::Push(AActor* Actor, bool& Success_Out)
{
	Success_Out = false;
	if(IsValid(Actor))
	{
		if(IArrowPoolInterface* PooledArrow = Cast<IArrowPoolInterface>(Actor))
		{
			InactivePool.Add(Actor);

			// Remove from active pool
			if(const int32 i = ActivePool.Find(Actor); i != INDEX_NONE)
			{
				ActivePool.RemoveAt(i, 1, false);
			}
			
			// Reset + disable actor
			if(Actor->GetActorEnableCollision()) Actor->SetActorEnableCollision(false);
			Actor->SetActorHiddenInGame(true);
			PooledArrow->OnPushed();
			
			Success_Out = true;
		}
	}
}
void UArrowShooterComponent::Pull(AActor*& Actor_Out, bool& Success_Out)
{
	Success_Out = false;

	// Find first available inactive arrow
	for (int i = 0; i < InactivePool.Num(); ++i)
	{
		if(IsValid(InactivePool[i]))
		{
			Actor_Out = ActivePool[ActivePool.Add(InactivePool[i])];
			InactivePool.Remove(Actor_Out);

			if(IArrowPoolInterface* PooledArrow = Cast<IArrowPoolInterface>(Actor_Out))
			{
				if(!Actor_Out->GetActorEnableCollision()) Actor_Out->SetActorEnableCollision(true);
				Actor_Out->SetActorHiddenInGame(false);
				PooledArrow->OnPulled();
			}
			Success_Out = true;
			return;
		}
	}

	// Reuse the oldest active arrow if inactive pool is empty
	if(!Success_Out)
	{
		if(ActivePool.Num() > 0 && IsValid(ActivePool[0]))
		{
			Actor_Out = ActivePool[0];
			if(IArrowPoolInterface* PooledArrow = Cast<IArrowPoolInterface>(Actor_Out))
			{
				ActivePool.Remove(Actor_Out);
				PooledArrow->OnPushed();
				ActivePool.Add(Actor_Out);
				if(!Actor_Out->GetActorEnableCollision()) Actor_Out->SetActorEnableCollision(true);
				PooledArrow->OnPulled();
			}
			Success_Out = true;
		}
	}
}

AActor* UArrowShooterComponent::SpawnArrow()
{
	if(UWorld* World = GetWorld())
	{
		FActorSpawnParameters* SpawnParameters = new FActorSpawnParameters;
		SpawnParameters->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if(AActor* SpawnedActor = World->SpawnActor<AActor>(ArrowClass,FVector::ZeroVector, FRotator::ZeroRotator, *SpawnParameters); IsValid(SpawnedActor))
		{
			bool Success;
			Push(SpawnedActor, Success);
			if(!Success) return nullptr;
			
			if(AArrow* SpawnedArrow = Cast<AArrow>(SpawnedActor))
			{
				SpawnedArrow->AssignToShooter(this);
			} 
			return SpawnedActor;
		}
	}
	return nullptr;
}

void UArrowShooterComponent::Shoot()
{
	AActor* PulledActor;
	bool Success;
	Pull(PulledActor, Success);
	if(!Success) return;
	
	if(AArrow* ShotArrow = Cast<AArrow>(PulledActor))
	{
		ShotArrow->SetActorLocation(GetComponentLocation());
		ShotArrow->ArrowMovementComponent->Velocity = (CalculateShotDirection() * ArrowSpeed);
	}
}

FVector UArrowShooterComponent::CalculateShotDirection()
{
	FVector CalculatedShotDirection;
	
	if(TargetPawn)
	{
		FVector PawnLocation = TargetPawn->GetActorLocation();
		
		CalculatedShotDirection = PawnLocation + AimOffset - GetComponentLocation();
		
		if(UPrimitiveComponent* MovementBase = TargetPawn->GetMovementBase())
		{
			// Perform a prediction is the player is standing on a moving platform
			// (not fully accurate but close enough)
			if(AActor* Platform = MovementBase->GetOwner())
			{
				const FVector PlatformVelocity = Platform->GetVelocity();
				
				if(PlatformVelocity != FVector::ZeroVector)
				{
					float DistanceToPawn = CalculatedShotDirection.Size();
					float TimeOfFlight = DistanceToPawn / ArrowSpeed;
		
					CalculatedShotDirection += PlatformVelocity * TimeOfFlight;
				}
			}
		}
	}
	else CalculatedShotDirection = ShotDirection;

	if(VerticalSpread != 0) CalculatedShotDirection.Z += FMath::RandRange(VerticalSpread, -VerticalSpread);
	if(HorizontalSpread != 0)
	{
		CalculatedShotDirection.X += FMath::RandRange(HorizontalSpread, -HorizontalSpread);
		CalculatedShotDirection.Y += FMath::RandRange(HorizontalSpread, -HorizontalSpread);
	}
	
	CalculatedShotDirection.Normalize();
	return CalculatedShotDirection;
}
