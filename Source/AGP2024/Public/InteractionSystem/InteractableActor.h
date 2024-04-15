// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class UBoxComponent;

UCLASS()
class AGP2024_API AInteractableActor : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "InteractableActor")
	UStaticMeshComponent* ActorMesh;

	// The box the player needs to look at in order to interact with the actor
	UPROPERTY(EditDefaultsOnly, Category = "InteractableActor")
	UBoxComponent* InteractionBox;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
