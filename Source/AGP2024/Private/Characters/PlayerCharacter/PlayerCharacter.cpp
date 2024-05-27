#include "Characters/PlayerCharacter/PlayerCharacter.h"
#include "Characters/PlayerCharacter/CharacterInteractionComponent.h"
#include "Characters/PlayerCharacter/CustomCharacterMovement.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerCharacter/PlayerCombatComponent.h"
#include "Components/InputComponent.h"

const FName NAME_WeaponSocket(TEXT("weapon_R"));

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super
(ObjectInitializer.SetDefaultSubobjectClass<UCustomCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
	CustomCharacterMovement = Cast<UCustomCharacterMovement>(GetCharacterMovement());
	
	PrimaryActorTick.bCanEverTick = false;
	
	// Create ArmsMesh
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ArmsMesh->SetupAttachment(GetMesh());
	ArmsMesh->CastShadow = false;

	// Create WeaponMesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetupAttachment(ArmsMesh, NAME_WeaponSocket);
	WeaponMesh->CastShadow = false;

	// Create CharacterInteractionComponent
	CharacterInteractionComponent = CreateDefaultSubobject<UCharacterInteractionComponent>(TEXT("InteractionComponent"));

	// Create CombatComponent
	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("CombatComponent"));
	CustomCharacterMovement->bCanWalkOffLedgesWhenCrouching = true;
}

void APlayerCharacter::Damage()
{
	UE_LOG(LogTemp, Warning, TEXT("Player was hit"))
	
	if(PlayerCombatComponent && !bIsImmuneToDamage)
	{
		PlayerCombatComponent->OnDefeated();
	}
}

void APlayerCharacter::EnableCharacterInput(bool EnableInput)
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if(EnableInput && !Subsystem->HasMappingContext(PlayerCharacterMappingContext))
			{
				Subsystem->AddMappingContext(PlayerCharacterMappingContext, 0);
				bCharacterInputEnabled = true;
				return;
			}
			if(!EnableInput && Subsystem->HasMappingContext(PlayerCharacterMappingContext))
			{
				Subsystem->RemoveMappingContext(PlayerCharacterMappingContext);
				bCharacterInputEnabled = false;
				return;
			}
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerCharacterMappingContext, 0);
			bCharacterInputEnabled = true;
		}
		
		UCustomCharacterMovement* CustomMovementTemp = GetComponentByClass<UCustomCharacterMovement>();
		check(CustomMovementTemp)
		UCharacterInteractionComponent* CharacterInteractionTemp = GetComponentByClass<UCharacterInteractionComponent>();
		check(CharacterInteractionTemp)
		UPlayerCombatComponent* CombatCompTemp = GetComponentByClass<UPlayerCombatComponent>();
		check(CombatCompTemp)
		
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
				&UCharacterInteractionComponent::OnInteractInputReceived);
			
			EnhancedInputComponent->BindAction(
				AttackAction,
				ETriggerEvent::Triggered,
				CombatCompTemp,
				&UPlayerCombatComponent::OnAttackInputReceived);
		}
	}
}
