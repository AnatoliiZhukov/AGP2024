#include "Characters/EnemyCharacter/EnemyCombatComponent.h"

#include "Characters/EnemyCharacter/EnemyCharacter.h"

UEnemyCombatComponent::UEnemyCombatComponent()
{
	AttackCooldown = 2.0f;
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