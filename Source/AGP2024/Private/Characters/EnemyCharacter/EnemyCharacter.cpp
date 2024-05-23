#include "Characters/EnemyCharacter/EnemyCharacter.h"

#include "Characters/EnemyCharacter/EnemyCombatComponent.h"
#include "Characters/EnemyCharacter/EnemySensingComponent.h"
#include "CombatSystem/ArrowShooterComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Set to react to player attacks
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);

	// Create EnemyArrowPool
	EnemyShooterComponent = CreateDefaultSubobject<UArrowShooterComponent>(TEXT("EnemyShooterComponent"));
	EnemyShooterComponent->ArrowSpeed = 2000.f;
	EnemyShooterComponent->SetupAttachment(GetMesh());

	// Create EnemySensingComponent
	EnemySensingComponent = CreateDefaultSubobject<UEnemySensingComponent>(TEXT("EnemySensingComponent"));
	EnemySensingComponent->bOnlySensePlayers = true;
	EnemySensingComponent->SensingInterval = .05f;
	EnemySensingComponent->SetPeripheralVisionAngle(80.f);
	EnemySensingComponent->bHearNoises = false;

	// Create EnemyCombatComponent
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(bIsDefeated) return;
	
	HandleInterest();
	HandleCharacterRotation(DeltaSeconds);
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EnemySensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultRotation = GetActorRotation();
}

void AEnemyCharacter::Damage()
{
	if(bIsDefeated) return;
	
	bIsDefeated = true;
	
	EnemySensingComponent->bEnableSensingUpdates = false;
	EnemySensingComponent->Deactivate();

	EnemyCombatComponent->OnDefeated();
	EnemyCombatComponent->Deactivate();

	SetActorEnableCollision(false);
}

void AEnemyCharacter::OnSeePawn(APawn* OtherPawn)
{
	if(!LookAtPawn) LookAtPawn = OtherPawn;
	
	if(const UWorld* World = GetWorld())
	{
		LastSeenTime = World->GetTimeSeconds();
		if(!EnemyCombatComponent->GetTargetPawn())
		{
			EnemyCombatComponent->SetTargetPawn(OtherPawn);
		}
	}

	if(EnemyCombatComponent)
	{
		EnemyCombatComponent->AttemptAttack();
	}
}

bool AEnemyCharacter::IsInterested() const
{
	if(const UWorld* World = GetWorld())
	{
		const float TimeSinceLastSeen = World->GetTimeSeconds() - LastSeenTime;
		return TimeSinceLastSeen < TimeUntilLosesInterest;
	}
	return false;
}

void AEnemyCharacter::HandleInterest()
{
	if(!IsInterested() && LookAtPawn)
	{
		LookAtPawn = nullptr;
	}
}

void AEnemyCharacter::HandleCharacterRotation(const float DT)
{
	FRotator TargetRotation;
	if(LookAtPawn)
	{
		FVector DirectionToTarget = LookAtPawn->GetActorLocation() - GetActorLocation();
		DirectionToTarget.Z = 0;
		TargetRotation = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();
	}
	else TargetRotation = DefaultRotation;
	const FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DT, RotationSpeed);
	SetActorRotation(NewRotation);
}