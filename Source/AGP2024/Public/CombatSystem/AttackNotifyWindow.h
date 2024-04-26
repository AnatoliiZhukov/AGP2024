#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "AttackNotifyWindow.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class AGP2024_API UAttackNotifyWindow : public UAnimNotify_PlayMontageNotifyWindow
{
	GENERATED_BODY()
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	UPROPERTY()
	APlayerCharacter* AttackingPlayerCharacter = nullptr;
};