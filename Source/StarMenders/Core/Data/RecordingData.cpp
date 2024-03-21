// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/RecordingData.h"

FRecordingDataFloat::FRecordingDataFloat()
{
}

FRecordingDataFloat::FRecordingDataFloat(float NewValue, float NewTick)
{
	Value = NewValue;
	Tick = NewTick;
}

FRecordingDataFloat::~FRecordingDataFloat()
{
}

// -----------------------------------------------

FRecordingDataVector::FRecordingDataVector()
{
}

FRecordingDataVector::FRecordingDataVector(FVector2D NewValue, float NewTick)
{
	Value = NewValue;
	Tick = NewTick;
}

FRecordingDataVector::~FRecordingDataVector()
{
}

// -----------------------------------------------

FRecordingData::FRecordingData()
{
}

FRecordingData::FRecordingData(TArray<FRecordingDataFloat> NewMoveXRecording, TArray<FRecordingDataFloat> NewMoveYRecording, TArray<float> NewJumpRecording, TArray<float> NewInteractRecording, TArray<FRecordingDataVector> NewCameraRecording)
{
	MoveXRecording = NewMoveXRecording;
	MoveYRecording = NewMoveYRecording;
	JumpRecording = NewJumpRecording;
	InteractRecording = NewInteractRecording;
	CameraRecording = NewCameraRecording;
}

FRecordingData::~FRecordingData()
{
}
