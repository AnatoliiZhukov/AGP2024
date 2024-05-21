#include "Characters/PlayerCharacter/AttackNotifyWindow.h"

#include "Characters/CombatComponentBase.h"

void UAttackNotifyWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if(UCombatComponentBase* CombatComponent = MeshComp->GetOwner()->GetComponentByClass<UCombatComponentBase>())
	{
		RelatedCombatComponent = CombatComponent;
	}
	
	if(RelatedCombatComponent && !RelatedCombatComponent->bAttackContinuously)
	{
		RelatedCombatComponent->Attack();
	}
}

void UAttackNotifyWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(RelatedCombatComponent && !RelatedCombatComponent->bAttackContinuously) return;
	
	if(RelatedCombatComponent)
	{
		RelatedCombatComponent->Attack();
	}
}