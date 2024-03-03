// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Player/Controller_Player.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/Character/Character_Parent.h"

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

	// Cast to the character pawn and store it
	Character = Cast<ACharacter_Parent>(GetPawn());
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
	}
}

/// -- Inputs --
void AController_Player::MoveX(const FInputActionValue& Value)
{
	if (Character) {
		Character->MoveX(Value.Get<float>());
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
}

void AController_Player::Interact(const FInputActionValue& Value)
{
}

void AController_Player::RotateCamera(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("value"));
	if (Character) {
		Character->RotateCamera(Value.Get<FVector2D>());
	}
}
