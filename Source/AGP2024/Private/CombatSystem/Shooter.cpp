


#include "CombatSystem/Shooter.h"

#include "CombatSystem/Arrow.h"
#include "CombatSystem/ArrowPoolComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShooter::AShooter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorTickInterval(0.25f);

	ShooterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShooterMesh"));
	RootComponent = ShooterMesh;
	
	ShooterArrowPool = CreateDefaultSubobject<UArrowPoolComponent>(TEXT("ShooterArrowPool"));
	ShooterArrowPool->InitialSpawnAmount = 10;
}

void AShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShooter::ShootArrow()
{
	if(ShooterArrowPool)
	{
		AActor* PulledActor;
		bool Result;
		ShooterArrowPool->Pull(PulledActor, Result);
		if(!Result) return;
	
		if(AArrow* Arrow = Cast<AArrow>(PulledActor))
		{
			Arrow->SetActorLocation(GetActorLocation());
			Arrow->ArrowMovementComponent->Velocity = ArrowDirection * ArrowSpeed;
		}
	}
}

void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsEnabled) return;
	
	ShootArrow();
}

void AShooter::SetIsEnabled(bool NewIsEnabled)
{
	bIsEnabled = NewIsEnabled;
}