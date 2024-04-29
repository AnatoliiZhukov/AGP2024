#include "Characters/EnemyCharacter/EnemyCharacter.h"

#include "Characters/EnemyCharacter/EnemySensingComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set to block player attacks
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);

	// Create EnemySensingComponent
	EnemySensingComponent = CreateDefaultSubobject<UEnemySensingComponent>(TEXT("EnemySensingComponent"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Damage()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy character hit"))
}

