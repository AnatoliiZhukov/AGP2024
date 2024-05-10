#include "CombatSystem/Arrow.h"

#include "Characters/EnemyCharacter/EnemyCharacter.h"
#include "CombatSystem/ArrowShooterComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ArrowCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ArrowCollision"));
	ArrowCollision->SetSphereRadius(5.f);
	ArrowCollision->SetCollisionResponseToAllChannels(ECR_Block);
	ArrowCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Ignore);
	RootComponent = ArrowCollision;

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	ArrowMesh->SetupAttachment(ArrowCollision);
	ArrowMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ArrowMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ArrowMovementComponent"));
	ArrowMovementComponent->Velocity = FVector(100.f, 0.f, 0.f);
	ArrowMovementComponent->ProjectileGravityScale = 0.f;
	ArrowMovementComponent->bRotationFollowsVelocity = true;
	ArrowMovementComponent->bInitialVelocityInLocalSpace = true;
	ArrowMovementComponent->InitialSpeed = 100.f;
	ArrowMovementComponent->MaxSpeed = 100.f;
}

void AArrow::Damage()
{
	PushToArrowPool();
}

void AArrow::OnPushed()
{
	ArrowMovementComponent->Deactivate();
	GetWorldTimerManager().ClearTimer(ArrowLifespanTimerHandle);
}

void AArrow::OnPulled()
{
	ArrowMovementComponent->Activate();
	GetWorldTimerManager().SetTimer(ArrowLifespanTimerHandle, this, &AArrow::OnArrowLifespanExpire, ArrowLifespan, false);
}

void AArrow::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(ArrowCollision)
	{
		ArrowCollision->OnComponentHit.AddDynamic(this, &AArrow::OnHit);
	}
}

void AArrow::OnArrowLifespanExpire()
{
	PushToArrowPool();
}

void AArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                   FVector NormalImpulse, const FHitResult& Hit)
{
	if(IDamageableInterface* HitDamageable = Cast<IDamageableInterface>(OtherActor))
	{
		HitDamageable->Damage();
		PushToArrowPool();
	}
	else
	{
		ArrowMovementComponent->Deactivate();
		SetActorEnableCollision(false);
	}
}

void AArrow::PushToArrowPool()
{
	if(AssignedShooter)
	{
		bool Success;
		AssignedShooter->Push(this, Success);
	}
}