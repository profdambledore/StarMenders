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

	// Called when 
	virtual void OnPossess(APawn* InPawn) override;

	// Called to make the character enter their menu
	void ToggleMenu(const FInputActionValue& Value);

	// Called to re-possess the original character
	void RePossessCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Inputs --
	// Called to move the character on the X axis
	void MoveX(const FInputActionInstance& Instance);

	// Called to move the character on the Y axis
	void MoveY(const FInputActionValue& Value);

	// Called to make the character jump
	void Jump(const FInputActionValue& Value);

	// Called to make the character interact
	void Interact(const FInputActionValue& Value);

	// Called to make the character's camera rotate
	void RotateCamera(const FInputActionValue& Value);

	// Called to make the character interact with their UI component
	void UIInteract(const FInputActionValue& Value);

	/// -- Recording Inputs --
	// MoveX input functions for beginning and ending
	void RecordMoveX(const FInputActionValue& Value);

	// MoveY input functions for beginning and ending
	void RecordMoveY(const FInputActionValue& Value);

	// MoveY input functions for beginning and ending
	void RecordCamera(const FInputActionValue& Value);

private:
	// Called to return a pointer based on which character this controller is currently possessing
	class ACharacter_Parent* GetActiveCharacter();

private:
	/// -- Controlled Character --
	// Pointer to the character this controller possesses
	class ACharacter_Default* Character = nullptr;

	// Pointer to the recording character this controller possesses
	class ACharacter_Record* RecordingCharacter = nullptr;

	// Bool denoting if the character is in their menu
	bool bInMenu = false;

	/// -- Inputs --
	// Pointer to the Input Config File
	class UInputConfigData* InputConfig = nullptr;

	// Pointer to the Input Mapping Context
	class UInputMappingContext* InputMapping = nullptr;
	
};
