// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/InteractableActor.h"

#include "Components/BoxComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create ActorMesh
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));

	// Create InteractionBox and set it to ignore everything except InteractTrace
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	
	RootComponent = ActorMesh;
	InteractionBox->SetupAttachment(ActorMesh);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction successful"))
}

