// Original ObjectPoolComponent: https://github.com/bennystarfighter/UnrealEngine-ObjectPool

#include "CombatSystem/ArrowPoolComponent.h"

#include "CombatSystem/ArrowPoolInterface.h"

UArrowPoolComponent::UArrowPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UArrowPoolComponent::Push(AActor* ArrowActor, bool& Success_Out)
{
	if (IsValid(ArrowActor))
	{
		if (IArrowPoolInterface* PooledArrow = Cast<IArrowPoolInterface>(ArrowActor))
		{
			InactivePool.Add(ArrowActor);

			// Remove from active pool
			if (int32 i = ActivePool.Find(ArrowActor); i != INDEX_NONE)
			{
				ActivePool.RemoveAt(i, 1, false);
			}
			else
			{
				i = NULL;
			}

			// Reset + disable actor
			ArrowActor->SetActorLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
			if (ArrowActor->GetActorEnableCollision())
			{
				ArrowActor->SetActorEnableCollision(false);
			}
			PooledArrow->OnPushed();
			Success_Out = true;
			return;
		}
	}
	Success_Out = false;
}

void UArrowPoolComponent::Pull(AActor*& ArrowActor_Out, bool& Success_Out)
{
	Success_Out = false;

	// Find first available inactive arrow
	for (int i = 0; i < InactivePool.Num(); ++i)
	{
		if (IsValid(InactivePool[i]))
		{
			ArrowActor_Out = ActivePool[ActivePool.Add(InactivePool[i])];
			InactivePool.Remove(ArrowActor_Out);

			if(IArrowPoolInterface* PooledArrow = Cast<IArrowPoolInterface>(ArrowActor_Out))
			{
				PooledArrow->OnPulled(this);
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
			ArrowActor_Out = ActivePool[0];
			if(IArrowPoolInterface* PooledArrow = Cast<IArrowPoolInterface>(ArrowActor_Out))
			{
				ActivePool.Remove(ArrowActor_Out);
				PooledArrow->OnPushed();
				ActivePool.Add(ArrowActor_Out);
				PooledArrow->OnPulled(this);
			}
			Success_Out = true;
		}
	}
}

AActor* UArrowPoolComponent::SpawnNewArrow()
{
	if (UWorld* World = this->GetWorld(); World != nullptr)
	{
		FActorSpawnParameters* SpawnParameters = new FActorSpawnParameters;
		SpawnParameters->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (AActor* SpawnedActor = World->SpawnActor<AActor>(ArrowClass,FVector::ZeroVector, FRotator::ZeroRotator, *SpawnParameters); IsValid(SpawnedActor))
		{
			bool Result;
			Push(SpawnedActor, Result);
			return SpawnedActor;
		}
	}
	return nullptr;
}

void UArrowPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < InitialSpawnAmount; ++i)
	{
		if (SpawnNewArrow() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ObjectPoolComponent spawned NULL AActor"));
		}
	}
}
