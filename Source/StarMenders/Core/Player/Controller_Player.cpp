// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Player/Controller_Player.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/Character/Character_Parent.h"
#include "Core/Character/Character_Record.h"

#include "Core/Inputs/InputConfigData.h"

AController_Player::AController_Player()
{
	// Find the input objects
	// First, find the Input Context Data
	ConstructorHelpers::FObjectFinder<UInputConfigData>ICDObject(TEXT("/Game/Core/Inputs/ICD_StarMenders"));
	if (ICDObject.Succeeded()) { InputConfig = ICDObject.Object; }

	// Last, find the Input Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext>IMCObject(TEXT("/Game/Core/Inputs/IMC_StarMenders"));
	if (IMCObject.Succeeded()) { InputMapping = IMCObject.Object; }
}

void AController_Player::BeginPlay()
{
	Super::BeginPlay();
}

void AController_Player::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if the input object pointers are valid
	if (InputConfig && InputMapping) {
		// Get and store the local player subsystem
		auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		// Then clear any existing mapping, then add the new mapping
		EnhancedInputSubsystem->ClearAllMappings();
		EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

		// Get the EnhancedInputComponent
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		// Bind the inputs
		EnhancedInputComponent->BindAction(InputConfig->MoveXInput, ETriggerEvent::Triggered, this, &AController_Player::MoveX);
		EnhancedInputComponent->BindAction(InputConfig->MoveYInput, ETriggerEvent::Triggered, this, &AController_Player::MoveY);
		EnhancedInputComponent->BindAction(InputConfig->JumpInput, ETriggerEvent::Triggered, this, &AController_Player::Jump);
		EnhancedInputComponent->BindAction(InputConfig->InteractInput, ETriggerEvent::Triggered, this, &AController_Player::Interact);
		EnhancedInputComponent->BindAction(InputConfig->CameraInput, ETriggerEvent::Triggered, this, &AController_Player::RotateCamera);
		EnhancedInputComponent->BindAction(InputConfig->MenuInput, ETriggerEvent::Triggered, this, &AController_Player::ToggleMenu);
		EnhancedInputComponent->BindAction(InputConfig->UIInteractInput, ETriggerEvent::Triggered, this, &AController_Player::UIInteract);
	}
}

void AController_Player::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Check if the pawn is a Character_Record.  If so, cast and set the pointer to it
	if (InPawn->IsA(ACharacter_Record::StaticClass())) {
		RecordingCharacter = Cast<ACharacter_Record>(InPawn);
		bInMenu = false;
		bShowMouseCursor = false;

		// Also hide the main character
		Character->SetActorHiddenInGame(true);
		Character->SetActorEnableCollision(false);
	}
	else if (InPawn->IsA(ACharacter_Parent::StaticClass())){
		RecordingCharacter = nullptr;

		if (!Character) {
			// Cast to the character pawn and store it
			Character = Cast<ACharacter_Parent>(GetPawn());
		}

		Character->SetActorHiddenInGame(false);
		Character->SetActorEnableCollision(true);
	}
}

void AController_Player::RePossessCharacter()
{
	this->Possess(Character);
}

/// -- Inputs --
void AController_Player::MoveX(const FInputActionInstance& Instance)
{
	if (Character) {
		GetActiveCharacter()->MoveX(Instance.GetValue().Get<float>());
	}
}

void AController_Player::MoveY(const FInputActionValue& Value)
{
	if (Character) {
		GetActiveCharacter()->MoveY(Value.Get<float>());
	}
}

void AController_Player::Jump(const FInputActionValue& Value)
{
	if (Character) {
		GetActiveCharacter()->StartJump();
	}
}

void AController_Player::Interact(const FInputActionValue& Value)
{
	if (Character) {
		GetActiveCharacter()->Interact();
	}
}

void AController_Player::RotateCamera(const FInputActionValue& Value)
{
	if (Character) {
		GetActiveCharacter()->RotateCamera(Value.Get<FVector2D>());
	}
}

void AController_Player::ToggleMenu(const FInputActionValue& Value)
{
	if (Character) {
		bInMenu = !bInMenu;
		GetActiveCharacter()->ToggleMenu(bInMenu);
		bShowMouseCursor = bInMenu;
	}
}

void AController_Player::UIInteract(const FInputActionValue& Value)
{
	if (Character) {
		GetActiveCharacter()->UIInteract(bInMenu);
	}
}

ACharacter_Parent* AController_Player::GetActiveCharacter()
{
	if (RecordingCharacter) {
		return RecordingCharacter;
	}
	return Character;
}
