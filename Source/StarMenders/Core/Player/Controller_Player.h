// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InputAction.h"
#include "Engine/DataAsset.h"

#include "Controller_Player.generated.h"

UCLASS()
class STARMENDERS_API AController_Player : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	AController_Player();

	// Called to setup the inputs for this player controller
	virtual void SetupInputComponent() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Inputs --
	// Called to move the character on the X axis
	void MoveX(const FInputActionValue& Value);

	// Called to move the character on the Y axis
	void MoveY(const FInputActionValue& Value);

	// Called to make the character jump
	void Jump(const FInputActionValue& Value);

	// Called to make the character interact
	void Interact(const FInputActionValue& Value);

	// Called to make the character's camera rotate
	void RotateCamera(const FInputActionValue& Value);

private:
	/// -- Controlled Character --
	// Pointer to the character this controller possesses
	class ACharacter_Parent* Character = nullptr;

	/// -- Inputs --
	// Pointer to the Input Config File
	class UInputConfigData* InputConfig = nullptr;

	// Pointer to the Input Mapping Context
	class UInputMappingContext* InputMapping = nullptr;
	
};
