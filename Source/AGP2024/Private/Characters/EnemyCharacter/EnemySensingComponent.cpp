


#include "Characters/EnemyCharacter/EnemySensingComponent.h"

void UEnemySensingComponent::OnSeePawn(APawn& Pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy sees player"))
}
