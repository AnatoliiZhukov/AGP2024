#include "CombatSystem/AttackNotifyWindow.h"

#include "Characters/PlayerCharacter.h"
#include "CombatSystem/CombatComponent.h"

void UAttackNotifyWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if(!AttackingPlayerCharacter)
	{
		AttackingPlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
	}
}

void UAttackNotifyWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if(AttackingPlayerCharacter)
	{
		AttackingPlayerCharacter->CombatComponent->Attack();
	}
}
