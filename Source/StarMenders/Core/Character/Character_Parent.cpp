// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Parent.h"

// Sets default values
ACharacter_Parent::ACharacter_Parent()
{
	// Setup the character's components
	// Setup the Player's Cameras
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetupAttachment(GetMesh(), "");

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacter_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacter_Parent::MoveX(float AxisValue)
{
	if (AxisValue != 0 && !bMovementDisabled) {
		// Move on the X axis based on the input's axis value
		AddMovementInput(FirstPersonCamera->GetForwardVector(), AxisValue, false);
	}
}

void ACharacter_Parent::MoveY(float AxisValue)
{
	if (AxisValue != 0 && !bMovementDisabled) {
		// Move on the X axis based on the input's axis value
		AddMovementInput(FirstPersonCamera->GetRightVector(), AxisValue, false);
	}
}

void ACharacter_Parent::StartJump()
{
	Jump();
}

void ACharacter_Parent::Interact()
{
}

void ACharacter_Parent::RotateCamera(FVector2D AxisValue)
{
	if (AxisValue.X != 0 && !bMovementDisabled) {
		// Rotate on the X axis based on the input's axis value
		AddControllerYawInput(AxisValue.X);
	}
	if (AxisValue.Y != 0 && !bMovementDisabled) {
		// Rotate on the Y axis based on the input's axis value
		AddControllerPitchInput(AxisValue.Y);
	}
}

