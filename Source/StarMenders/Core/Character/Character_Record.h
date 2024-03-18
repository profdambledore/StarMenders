// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/Character_Parent.h"

#include "InputAction.h"
#include "Engine/DataAsset.h"

#include "Character_Record.generated.h"

// Struct holding the data of an input recording
USTRUCT(BlueprintType, Category = "Recording")
struct STARMENDERS_API FRecordingData
{
public:
	GENERATED_BODY();

	/// -- Recording Data --
	// The value of the input at the tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording Data")
	float Value;

	// The tick associated with this value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording Data")
	float Tick;

public:
	FRecordingData();
	FRecordingData(float NewValue, float NewTick);
	~FRecordingData();
};

UCLASS()
class STARMENDERS_API ACharacter_Record : public ACharacter_Parent
{
	GENERATED_BODY()

public:
	ACharacter_Record();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
	
protected:
	/// -- Inputs --
	// Pointer to the Input Config File
	class UInputConfigData* InputConfig = nullptr;

	// Pointer to the Input Mapping Context
	class UInputMappingContext* InputMapping = nullptr;

	/// -- Input Booleans --
	// Bool for each input to denote if the input is currently being pressed
	bool bMoveXActive = false;

	/// -- Recording --
	// Timer handle for the recording tick
	FTimerHandle RecordingTickHandle;

	// Timer handle for the total recording time
	FTimerHandle RecordingTotalHandle;

	// Float denoting the maximum time allowed to record
	float MaximumRecordingTime = 60.0f;

	// Float denoting the current tick time
	float CurrentTickTime = 0.0f;

	// -- RecordedInputs --
	// TArray storing all recorded MoveX inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	TArray<FRecordingData> MoveXRecording;

private:
	/// -- Input Value Binds --
	struct FEnhancedInputActionValueBinding* MoveXBind;
};
