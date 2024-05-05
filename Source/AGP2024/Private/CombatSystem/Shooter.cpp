


#include "CombatSystem/Shooter.h"

AShooter::AShooter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorTickInterval(0.25f);
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooter::SetIsEnabled(bool NewIsEnabled)
{
	bIsEnabled = NewIsEnabled;
}

