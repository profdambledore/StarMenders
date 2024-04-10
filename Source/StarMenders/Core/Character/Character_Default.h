// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/Character_Parent.h"

#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"

#include "Core/Data/RecordingData.h"

#include "Character_Default.generated.h"

UCLASS()
class STARMENDERS_API ACharacter_Default : public ACharacter_Parent
{
	GENERATED_BODY()
	
public:
	ACharacter_Default();

	/// -- Inputs --
	// Called to move the character on the X axis
	virtual void MoveX(float AxisValue);

	// Called to move the character on the Y axis
	virtual void MoveY(float AxisValue);

	// Called to make the character's camera rotate
	virtual void RotateCamera(FVector2D AxisValue);

	// Called to make the camera jump
	virtual void StartJump();

	// Called to make the character interact
	virtual void Interact();

	// Called to make the character enter their menu
	void ToggleMenu(bool bInMenu);

	// Called to make the character interact with their UI element
	void UIInteract(bool bInMenu);

	// MoveX input functions for beginning and ending
	void RecordMoveX();

	// MoveY input functions for beginning and ending
	void RecordMoveY();

	// MoveY input functions for beginning and ending
	void RecordCamera();

	/// -- Recording --
	// Called to start a recording
	void StartRecording(class ARecordPad* NewRecordPad);

	// Timer event for the total duration of the recording
	void EndRecording();

	/// -- Interaction --
	// Called to return CurrentRecordPad
	class ARecordPad* GetCurrentRecordPad();

	// Called to set the CurrentRecordPad
	void SetCurrentRecordPad(class ARecordPad* NewRecordPad);

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Recording --
	// Timer event for each tick of the recording
	void RecordingTick();

public:
	/// -- Components --
	// WidgetComponent used to display the InGame UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* MenuWidgetComponent;

	// WidgetInteractionComponent used to interact with MenuWidgetComponent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetInteractionComponent* WidgetInteractionComponent;

	/// -- Input Value Binds --
	struct FEnhancedInputActionValueBinding* MoveXBind;
	struct FEnhancedInputActionValueBinding* MoveYBind;
	struct FEnhancedInputActionValueBinding* CameraBind;

protected:
	/// -- Recording --
	// Bool for if the recording is active
	bool bCurrentlyRecording = false;

	// Bool for each input to denote if the input is currently being pressed
	bool bMoveXActive = false;
	bool bMoveYActive = false;
	bool bCameraActive = false;

	// Timer handle for the recording tick
	FTimerHandle RecordingTickHandle;

	// Timer handle for the total recording time
	FTimerHandle RecordingTotalHandle;

	// Float denoting the maximum time allowed to record
	float MaximumRecordingTime = 60.0f;

	// Float denoting the current tick time
	float CurrentTickTime = 0.0f;

	// Pointer to the record pad currently being accessed
	class ARecordPad* CurrentRecordPad = nullptr;

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

	/// -- UI --
	// Pointer to the UI added to the viewport
	class UInGame_Master* MenuUI = nullptr;
};
