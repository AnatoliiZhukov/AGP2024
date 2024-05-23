#include "Characters/EnemyCharacter/EnemyCombatComponent.h"

#include "Characters/EnemyCharacter/EnemyCharacter.h"
#include "CombatSystem/ArrowShooterComponent.h"
#include "CombatSystem/LevelManagerWorldSub.h"

UEnemyCombatComponent::UEnemyCombatComponent()
{
	AttackCooldown = 2.5f;
	bAttackContinuously = false;
}

void UEnemyCombatComponent::Attack()
{
	Super::Attack();

	if(OwningEnemyCharacter && OwningEnemyCharacter->GetEnemyShooter() && TargetPawn)
	{
		if(UArrowShooterComponent* EnemyShooter = OwningEnemyCharacter->GetEnemyShooter())
		{
			FVector NewShotDirection = TargetPawn->GetActorLocation() + AimOffset - EnemyShooter->GetComponentLocation();
			NewShotDirection.Normalize();
			EnemyShooter->SetShotDirection(NewShotDirection);
			OwningEnemyCharacter->GetEnemyShooter()->Shoot();
		}
	}
}

void UEnemyCombatComponent::OnDefeated()
{
	Super::OnDefeated();

	EnemyCharacterMeshAnimInstance->Montage_Stop(NULL);

	OnEnemyDefeated.Broadcast();
	
	if(UWorld* World = GetWorld())
	{
		World->GetSubsystem<ULevelManagerWorldSub>(World)->BroadcastOnAnyEnemyDefeated();
	}
}

void UEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningEnemyCharacter = CastChecked<AEnemyCharacter>(GetOwner());
	
	if (OwningEnemyCharacter->GetMesh())
	{
		EnemyCharacterMeshAnimInstance = OwningEnemyCharacter->GetMesh()->GetAnimInstance();
		check(EnemyCharacterMeshAnimInstance)
	}
}

void UEnemyCombatComponent::AttemptAttack()
{
	if(AttackIsOnCooldown()) return;
	
	if(EnemyCharacterMeshAnimInstance && AttackMontage)
	{
		if(!EnemyCharacterMeshAnimInstance->Montage_IsPlaying(NULL))
		{
			EnemyCharacterMeshAnimInstance->Montage_Play(AttackMontage);
			
			if(const UWorld* World = GetWorld())
			{
				LastAttackTime = World->GetTimeSeconds();
			}
		}
	}
}