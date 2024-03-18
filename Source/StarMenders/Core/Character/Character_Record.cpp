// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Record.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/Inputs/InputConfigData.h"

FRecordingData::FRecordingData()
{
}

FRecordingData::FRecordingData(float NewValue, float NewTick)
{
	Value = NewValue;
	Tick = NewTick;
}

FRecordingData::~FRecordingData()
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

// ---------------------------------------------------

ACharacter_Record::ACharacter_Record()
{
	// Find the input objects
	// First, find the Input Context Data
	ConstructorHelpers::FObjectFinder<UInputConfigData>ICDObject(TEXT("/Game/Core/Inputs/ICD_StarMenders"));
	if (ICDObject.Succeeded()) { InputConfig = ICDObject.Object; }

	// Last, find the Input Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext>IMCObject(TEXT("/Game/Core/Inputs/IMC_StarMenders"));
	if (IMCObject.Succeeded()) { InputMapping = IMCObject.Object; }
}

void ACharacter_Record::BeginPlay()
{
	Super::BeginPlay();

	CurrentTickTime = 0.0f;

	// Setup two timers for this buff - the buff tick and the total buff duration
	GetWorld()->GetTimerManager().SetTimer(RecordingTickHandle, FTimerDelegate::CreateUObject(this, &ACharacter_Record::RecordingTick), TimerTickRate, true, TimerTickRate);
	GetWorld()->GetTimerManager().SetTimer(RecordingTotalHandle, FTimerDelegate::CreateUObject(this, &ACharacter_Record::EndRecording), MaximumRecordingTime, false, MaximumRecordingTime);
}

void ACharacter_Record::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Check if the input object pointers are valid
	if (InputConfig && InputMapping) {
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

		EnhancedInputComponent->BindAction(InputConfig->MoveXInput, ETriggerEvent::Started, this, &ACharacter_Record::RecordMoveX);
		EnhancedInputComponent->BindAction(InputConfig->MoveXInput, ETriggerEvent::Completed, this, &ACharacter_Record::RecordMoveX);
		EnhancedInputComponent->BindAction(InputConfig->MoveYInput, ETriggerEvent::Started, this, &ACharacter_Record::RecordMoveY);
		EnhancedInputComponent->BindAction(InputConfig->MoveYInput, ETriggerEvent::Completed, this, &ACharacter_Record::RecordMoveY);
		EnhancedInputComponent->BindAction(InputConfig->JumpInput, ETriggerEvent::Started, this, &ACharacter_Record::RecordJump);
		EnhancedInputComponent->BindAction(InputConfig->InteractInput, ETriggerEvent::Started, this, &ACharacter_Record::RecordInteract);
		EnhancedInputComponent->BindAction(InputConfig->CameraInput, ETriggerEvent::Started, this, &ACharacter_Record::RecordCamera);
		EnhancedInputComponent->BindAction(InputConfig->CameraInput, ETriggerEvent::Completed, this, &ACharacter_Record::RecordCamera);

		MoveXBind = &EnhancedInputComponent->BindActionValue(InputConfig->MoveXInput);
		MoveYBind = &EnhancedInputComponent->BindActionValue(InputConfig->MoveYInput);
		CameraBind = &EnhancedInputComponent->BindActionValue(InputConfig->CameraInput);
	}
}

void ACharacter_Record::RecordingTick()
{
	// Record each of the active inputs at this tick
	// Record MoveX tick
	if (bMoveXActive) {
		MoveXRecording.Add(FRecordingData( MoveXBind->GetValue().Get<float>(), CurrentTickTime));
	}

	if (bMoveYActive) {
		MoveYRecording.Add(FRecordingData(MoveYBind->GetValue().Get<float>(), CurrentTickTime));
	}

	if (bCameraActive) {
		CameraRecording.Add(FRecordingDataVector(MoveYBind->GetValue().Get<FVector2D>(), CurrentTickTime));
	}

	// Finally, increment CurrentTickTime
	CurrentTickTime += TimerTickRate;
}

void ACharacter_Record::EndRecording()
{
	// Clear the timer handles
	GetWorld()->GetTimerManager().ClearTimer(RecordingTickHandle);
	GetWorld()->GetTimerManager().ClearTimer(RecordingTotalHandle);
}

void ACharacter_Record::RecordMoveX(const FInputActionValue& Value)
{
	// Check if this is either the start or end of the input
	// If bMoveXActive is true at this stage, the input has been completed
	if (bMoveXActive) {
		bMoveXActive = false;
	}
	else {
		bMoveXActive = true;
	}
}

void ACharacter_Record::RecordMoveY(const FInputActionValue& Value)
{
	// Check if this is either the start or end of the input
	// If bMoveXActive is true at this stage, the input has been completed
	if (bMoveYActive) {
		bMoveYActive = false;
	}
	else {
		bMoveYActive = true;
	}
}

void ACharacter_Record::RecordJump()
{
	JumpRecording.Add(CurrentTickTime);
}

void ACharacter_Record::RecordInteract()
{
	InteractRecording.Add(CurrentTickTime);
}

void ACharacter_Record::RecordCamera(const FInputActionValue& Value)
{
	if (bCameraActive) {
		bCameraActive = false;
	}
	else {
		bCameraActive = true;
	}
}

