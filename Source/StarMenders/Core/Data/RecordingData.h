// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "RecordingData.generated.h"

// Struct holding the data of an input float recording
USTRUCT(BlueprintType, Category = "Recording")
struct STARMENDERS_API FRecordingDataFloat
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
	FRecordingDataFloat();
	FRecordingDataFloat(float NewValue, float NewTick);
	~FRecordingDataFloat();
};

// Struct holding the data of an input FVector recording
USTRUCT(BlueprintType, Category = "Recording")
struct STARMENDERS_API FRecordingDataVector
{
public:
	GENERATED_BODY();

	/// -- Recording Data --
	// The value of the input at the tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording Data")
	FVector2D Value;

	// The tick associated with this value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recording Data")
	float Tick;

public:
	FRecordingDataVector();
	FRecordingDataVector(FVector2D NewValue, float NewTick);
	~FRecordingDataVector();
};

// Struct holding the data of an recording
USTRUCT(BlueprintType, Category = "Recording")
struct STARMENDERS_API FRecordingData
{
public:
	GENERATED_BODY();

	/// -- Recording Data --
	// TArray storing all recorded MoveX inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recording Data");
	TArray<FRecordingDataFloat> MoveXRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recording Data");
	TArray<FRecordingDataFloat> MoveYRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recording Data");
	TArray<float> JumpRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recording Data");
	TArray<float> InteractRecording;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recording Data");
	TArray<FRecordingDataVector> CameraRecording;

public:
	FRecordingData();
	FRecordingData(TArray<FRecordingDataFloat> NewMoveXRecording, TArray<FRecordingDataFloat> NewMoveYRecording, TArray<float> NewJumpRecording, TArray<float> NewInteractRecording, TArray<FRecordingDataVector> NewCameraRecording);
	~FRecordingData();
};