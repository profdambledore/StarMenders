// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/Character_Parent.h"

#include "InputAction.h"
#include "Engine/DataAsset.h"

#include "Core/Data/RecordingData.h"

#include "Character_Record.generated.h"

UCLASS()
class STARMENDERS_API ACharacter_Record : public ACharacter_Parent
{
	GENERATED_BODY()

public:
	ACharacter_Record();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to start a recording
	void StartRecording(class ARecordPad* NewRecordPad);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Recording Tick Timers --
	// Timer event for each tick of the recording
	void RecordingTick();

	// Timer event for the total duration of the recording
	void EndRecording();

	/// -- Inputs --
	// MoveX input functions for beginning and ending
	void RecordMoveX(const FInputActionValue& Value);

	// MoveY input functions for beginning and ending
	void RecordMoveY(const FInputActionValue& Value);

	// Jump input function
	void RecordJump();

	// Interact input function
	void RecordInteract();

	// MoveY input functions for beginning and ending
	void RecordCamera(const FInputActionValue& Value);
	
protected:
	/// -- Inputs --
	// Pointer to the Input Config File
	class UInputConfigData* InputConfig = nullptr;

	// Pointer to the Input Mapping Context
	class UInputMappingContext* InputMapping = nullptr;

	/// -- Input Booleans --
	// Bool for each input to denote if the input is currently being pressed
	bool bMoveXActive = false;
	bool bMoveYActive = false;
	bool bCameraActive = false;

	/// -- Recording --
	// Pointer to the record pad where the recording will be stored
	ARecordPad* OwningRecordPad = nullptr;

	// Timer handle for the recording tick
	FTimerHandle RecordingTickHandle;

	// Timer handle for the total recording time
	FTimerHandle RecordingTotalHandle;

	// Float denoting the maximum time allowed to record
	float MaximumRecordingTime = 5.0f;

	// Float denoting the current tick time
	float CurrentTickTime = 0.0f;

	// -- RecordedInputs --
	// TArray storing all recorded MoveX inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recordings");
	TArray<FRecordingDataFloat> MoveXRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recordings");
	TArray<FRecordingDataFloat> MoveYRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recordings");
	TArray<float> JumpRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recordings");
	TArray<float> InteractRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recordings");
	TArray<FRecordingDataVector> CameraRecording;

private:
	/// -- Input Value Binds --
	struct FEnhancedInputActionValueBinding* MoveXBind;
	struct FEnhancedInputActionValueBinding* MoveYBind;
	struct FEnhancedInputActionValueBinding* CameraBind;
};
