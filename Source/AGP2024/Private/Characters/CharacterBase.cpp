// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterBase.h"

#include "Player/CustomCharacterMovement.h"

ACharacterBase::ACharacterBase(const FObjectInitializer& ObjectInitializer) : Super
(ObjectInitializer.SetDefaultSubobjectClass<UCustomCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	CustomCharacterMovement = Cast<UCustomCharacterMovement>(GetCharacterMovement());
	
	PrimaryActorTick.bCanEverTick = false;
}
