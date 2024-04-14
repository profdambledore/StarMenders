// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Default.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Core/Mechanics/RecordPad.h"
#include "Core/UI/InGame_Master.h"
#include "Core/UI/InGame_Recording.h"
#include "Core/Level/LevelController.h"
#include "Core/Player/Controller_Player.h"

ACharacter_Default::ACharacter_Default()
{
	// Setup the MenuWidgetComponent and the WidgetInteractionComponent
	MenuWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget Component"));
	MenuWidgetComponent->SetupAttachment(GetMesh(), "");
	MenuWidgetComponent->SetGenerateOverlapEvents(false);

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Interaction Component"));
	WidgetInteractionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;
	WidgetInteractionComponent->SetupAttachment(FirstPersonCamera, "");

	// Get the InGame UserWidget for the character and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Core/UI/WBP_InGame"));
	if (UIClass.Succeeded()) {
		MenuWidgetComponent->SetWidgetClass(UIClass.Class);
	};
}

// Called when the game starts or when spawned
void ACharacter_Default::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the interact widget class
	MenuUI = Cast<UInGame_Master>(MenuWidgetComponent->GetWidget());
	MenuUI->SetPlayerOwner(this);
}

void ACharacter_Default::MoveX(float AxisValue)
{
	if (AxisValue != 0 && !bMovementDisabled) {
		// Move on the X axis based on the input's axis value
		// Get the camera's forward vector X and Y, removing the Z
		FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
		Direction = FVector(Direction.X, Direction.Y, 0.0f).GetSafeNormal();
		AddMovementInput(Direction, AxisValue, false);
		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Default::MoveY(float AxisValue)
{
	ACharacter_Parent::MoveY(AxisValue);
}

void ACharacter_Default::StartJump()
{
	ACharacter_Parent::StartJump();

	if (bCurrentlyRecording) {
		JumpRecording.Add(CurrentTickTime);
	}
}

void ACharacter_Default::Interact()
{
	ACharacter_Parent::Interact();

	if (bCurrentlyRecording) {
		InteractRecording.Add(CurrentTickTime);
	}
}

void ACharacter_Default::RotateCamera(FVector2D AxisValue)
{
	if (!bMovementDisabled) {
		//UE_LOG(LogTemp, Warning, TEXT("Rotate = %f / %f"), AxisValue.X, AxisValue.Y);

		// Rotate on the X axis based on the input's axis value
		AddControllerYawInput(AxisValue.X);
		AddControllerPitchInput(AxisValue.Y);

		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Default::RecordMoveX()
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

void ACharacter_Default::RecordMoveY()
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

void ACharacter_Default::RecordCamera()
{
	if (bCameraActive) {
		bCameraActive = false;
	}
	else {
		bCameraActive = true;
	}
}

void ACharacter_Default::ToggleMenu(bool bInMenu)
{
	MenuWidgetComponent->SetVisibility(bInMenu);
	bMovementDisabled = bInMenu;
}

void ACharacter_Default::UIInteract(bool bInMenu)
{
	if (bInMenu) {
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	}
}

void ACharacter_Default::StartRecording(ARecordPad* NewRecordPad)
{
	bCurrentlyRecording = true;

	// Clear the arrays
	MoveXRecording.Empty();
	MoveYRecording.Empty();
	CameraRecording.Empty();
	JumpRecording.Empty();
	InteractRecording.Empty();

	MenuUI->UpdateActiveState("Recording");

	CurrentTickTime = 0.0f;
	bool bTeleportCharacter = true;

	// Setup two timers for this character - the recording tick and the total buff duration
	GetWorld()->GetTimerManager().SetTimer(RecordingTickHandle, FTimerDelegate::CreateUObject(this, &ACharacter_Default::RecordingTick), TimerTickRate, true, TimerTickRate);
	GetWorld()->GetTimerManager().SetTimer(RecordingTotalHandle, FTimerDelegate::CreateUObject(this, &ACharacter_Default::EndRecording, bTeleportCharacter), MaximumRecordingTime, false, MaximumRecordingTime);

	Cast<AController_Player>(GetController())->ToggleMenu(false);
}

void ACharacter_Default::RecordingTick()
{
	// Record each of the active inputs at this tick
	// Record MoveX tick
	if (bMoveXActive) {
		MoveXRecording.Add(FRecordingDataFloat(MoveXBind->GetValue().Get<float>(), CurrentTickTime));
	}

	if (bMoveYActive) {
		MoveYRecording.Add(FRecordingDataFloat(MoveYBind->GetValue().Get<float>(), CurrentTickTime));
	}

	if (bCameraActive) {
		CameraRecording.Add(FRecordingDataVector(FVector2D(GetControlRotation().Pitch, GetControlRotation().Yaw), CurrentTickTime));
	}

	// Finally, increment CurrentTickTime
	CurrentTickTime += TimerTickRate;

	MenuUI->RecordState->UpdateRemainingTime(MaximumRecordingTime - CurrentTickTime);
}

void ACharacter_Default::EndRecording(bool bTeleportCharacter)
{
	// Clear the timer handles
	GetWorld()->GetTimerManager().ClearTimer(RecordingTickHandle);
	GetWorld()->GetTimerManager().ClearTimer(RecordingTotalHandle);

	// Pass the recording to the recording pad associated with this recording character
	if (bTeleportCharacter) {
		CurrentRecordPad->SetRecording(FRecordingData(MoveXRecording, MoveYRecording, JumpRecording, InteractRecording, CameraRecording), this);
		Cast<AController_Player>(GetController())->ToggleMenu(false);
	}
	else {
		CurrentRecordPad->SetRecording(FRecordingData(MoveXRecording, MoveYRecording, JumpRecording, InteractRecording, CameraRecording));
	}

	// Call  on the LevelController
	Cast<ALevelController>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelController::StaticClass()))->EndLevelPlayback();

	MenuUI->UpdateActiveState("InGame");

	bCurrentlyRecording = false;
	SetCurrentRecordPad(nullptr);
}

ARecordPad* ACharacter_Default::GetCurrentRecordPad()
{
	return CurrentRecordPad;
}

void ACharacter_Default::SetCurrentRecordPad(ARecordPad* NewRecordPad)
{
	if (!bCurrentlyRecording) {
		CurrentRecordPad = NewRecordPad;
	}
	else {

	}
}

