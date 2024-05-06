#include "CombatSystem/Arrow.h"

#include "CombatSystem/ArrowPoolComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ArrowCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ArrowCollision"));
	ArrowCollision->SetSphereRadius(5.f);
	ArrowCollision->SetCollisionProfileName("IgnoreOnlyPawn");
	ArrowCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
	ArrowCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	ArrowCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
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
	UE_LOG(LogTemp, Warning, TEXT("Arrow hit"))
	PushToCurrentArrowPool();
}

void AArrow::OnPushed()
{
	SetActorHiddenInGame(true);
	ArrowMovementComponent->Deactivate();
}

void AArrow::OnPulled(UArrowPoolComponent* ArrowPool)
{
	if(!CurrentArrowPool) CurrentArrowPool = ArrowPool;
	
	SetActorHiddenInGame(false);
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
	PushToCurrentArrowPool();
}

void AArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                   FVector NormalImpulse, const FHitResult& Hit)
{
	if(IDamageableInterface* HitDamageable = Cast<IDamageableInterface>(OtherActor))
	{
		HitDamageable->Damage();
		PushToCurrentArrowPool();
	}
	else
	{
		ArrowMovementComponent->StopMovementImmediately();
		ArrowCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AArrow::PushToCurrentArrowPool()
{
	if(CurrentArrowPool)
	{
		bool Result;
		CurrentArrowPool->Push(this, Result);
	}
}
