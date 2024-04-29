#include "Characters/PlayerCharacter/AttackNotifyWindow.h"

#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "Characters/PlayerCharacter/CombatComponent.h"

void UAttackNotifyWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!AttackingPlayerCharacter)
	{
		AttackingPlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	}
}

void UAttackNotifyWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(AttackingPlayerCharacter)
	{
		AttackingPlayerCharacter->CombatComponent->Attack();
	}
}
