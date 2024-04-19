#include "Characters/PlayerCharacter.h"
#include "InteractionSystem/CharacterInteractionComponent.h"
#include "Player/CustomCharacterMovement.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationSystem.h"
#include "Components/InputComponent.h"

const FName NAME_WeaponSocket(TEXT("weapon_R"));

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super
(ObjectInitializer.SetDefaultSubobjectClass<UCustomCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	CustomCharacterMovement = Cast<UCustomCharacterMovement>(GetCharacterMovement());
	
	PrimaryActorTick.bCanEverTick = true;
	
	// Create ArmsMesh
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetupAttachment(GetMesh());
	ArmsMesh->CastShadow = false;

	// Create WeaponMesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(ArmsMesh, NAME_WeaponSocket);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create CharacterInteractionComponent
	CharacterInteractionComponent = CreateDefaultSubobject<UCharacterInteractionComponent>(TEXT("InteractionComponent"));
	
	CustomCharacterMovement->bCanWalkOffLedgesWhenCrouching = true;
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// Add mapping context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerCharacterMappingContext, 0);
		}
		
		UCustomCharacterMovement* CustomMovementTemp = GetComponentByClass<UCustomCharacterMovement>();
		check(CustomMovementTemp)
		UCharacterInteractionComponent* CharacterInteractionTemp = GetComponentByClass<UCharacterInteractionComponent>();
		check(CharacterInteractionTemp)
		
		// Bind functions to input actions
		if (UEnhancedInputComponent* EnhancedInputComponent =
			CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(
				MoveAction,
				ETriggerEvent::Triggered,
				CustomMovementTemp,
				&UCustomCharacterMovement::OnMoveInputReceived);
		
			EnhancedInputComponent->BindAction(
				LookAction,
				ETriggerEvent::Triggered,
				CustomMovementTemp,
				&UCustomCharacterMovement::OnLookInputReceived);
			
			EnhancedInputComponent->BindAction(
				JumpAction,
				ETriggerEvent::Triggered,
				CustomMovementTemp,
				&UCustomCharacterMovement::OnJumpInputReceived);
			
			EnhancedInputComponent->BindAction(
				CrouchAction,
				ETriggerEvent::Triggered,
				CustomMovementTemp,
				&UCustomCharacterMovement::OnCrouchInputReceived);
			
			EnhancedInputComponent->BindAction(
				SprintAction,
				ETriggerEvent::Triggered,
				CustomMovementTemp,
				&UCustomCharacterMovement::OnRunInputReceived);
			
			EnhancedInputComponent->BindAction(
				InteractAction,
				ETriggerEvent::Triggered,
				CharacterInteractionTemp,
				&UCharacterInteractionComponent::AttemptInteraction);
		}
	}
}