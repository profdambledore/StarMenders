 // Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Player/Controller_Player.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/Character/Character_Parent.h"
#include "Core/Character/Character_Default.h"
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
	
		EnhancedInputComponent->BindAction(InputConfig->MoveXInput, ETriggerEvent::Started, this, &AController_Player::RecordMoveX);
		EnhancedInputComponent->BindAction(InputConfig->MoveXInput, ETriggerEvent::Completed, this, &AController_Player::RecordMoveX);
		EnhancedInputComponent->BindAction(InputConfig->MoveYInput, ETriggerEvent::Started, this, &AController_Player::RecordMoveY);
		EnhancedInputComponent->BindAction(InputConfig->MoveYInput, ETriggerEvent::Completed, this, &AController_Player::RecordMoveY);
		EnhancedInputComponent->BindAction(InputConfig->CameraInput, ETriggerEvent::Started, this, &AController_Player::RecordCamera);
		EnhancedInputComponent->BindAction(InputConfig->CameraInput, ETriggerEvent::Completed, this, &AController_Player::RecordCamera);
	
	}
}

void AController_Player::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!Character) {
		// Cast to the character pawn and store it
		Character = Cast<ACharacter_Default>(GetPawn());
	}

	bInMenu = false;
	Character->ToggleMenu(bInMenu);
	bShowMouseCursor = bInMenu;		

	Character->SetActorHiddenInGame(false);
	Character->SetActorEnableCollision(true);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent) {
		Character->MoveXBind = &EnhancedInputComponent->BindActionValue(InputConfig->MoveXInput);
		Character->MoveYBind = &EnhancedInputComponent->BindActionValue(InputConfig->MoveYInput);
		Character->CameraBind = &EnhancedInputComponent->BindActionValue(InputConfig->CameraInput);
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
		Character->MoveX(Instance.GetValue().Get<float>());
	}
}

void AController_Player::MoveY(const FInputActionValue& Value)
{
	if (Character) {
		Character->MoveY(Value.Get<float>());
	}
}

void AController_Player::Jump(const FInputActionValue& Value)
{
	if (Character) {
		Character->StartJump();
	}
}

void AController_Player::Interact(const FInputActionValue& Value)
{
	if (Character) {
		Character->Interact();
	}
}

void AController_Player::RotateCamera(const FInputActionValue& Value)
{
	if (Character) {
		Character->RotateCamera(Value.Get<FVector2D>());
	}
}

void AController_Player::RecordMoveX(const FInputActionValue& Value)
{
	if (Character) {
		Character->RecordMoveX();
	}
}

void AController_Player::RecordMoveY(const FInputActionValue& Value)
{
	if (Character) {
		Character->RecordMoveY();
	}
}

void AController_Player::RecordCamera(const FInputActionValue& Value)
{
	if (Character) {
		Character->RecordCamera();
	}
}

void AController_Player::ToggleMenu(const FInputActionValue& Value)
{
	if (Character) {
		bInMenu = !bInMenu;
		Character->ToggleMenu(bInMenu);
		bShowMouseCursor = bInMenu;
	}
}

void AController_Player::UIInteract(const FInputActionValue& Value)
{
	if (Character) {
		Character->UIInteract(bInMenu);
	}
}

ACharacter_Parent* AController_Player::GetActiveCharacter()
{
	if (RecordingCharacter) {
		return RecordingCharacter;
	}
	return Character;
}
