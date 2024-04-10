// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Playback.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void ACharacter_Playback::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());

	//SetupPlayback(TEMP_Playback);
}

void ACharacter_Playback::MoveX(float AxisValue)
{
	if (AxisValue != 0 && !bMovementDisabled) {
		// Move on the X axis based on the input's axis value
		// Get the camera's forward vector X and Y, removing the Z
		FVector Direction = FRotationMatrix(FirstPersonCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
		Direction = FVector(Direction.X, Direction.Y, 0.0f).GetSafeNormal();
		AddMovementInput(Direction, AxisValue, false);
		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Playback::RotateCamera(FVector2D AxisValue)
{
	if (!bMovementDisabled) {
		// Update the FirstPersonCamera with the new pitch
		FirstPersonCamera->SetWorldRotation(FRotator(AxisValue.X, AxisValue.Y, 0.0f));
		SetActorRotation(FRotator(0.0f, AxisValue.Y, 0.0f));

		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Playback::SetupPlayback(FRecordingData NewPlayback)
{
	// Store the playback
	Playback = NewPlayback;

	TArray<float> b;
	if (Playback.MoveXRecording.IsEmpty()) {b.Insert(0, 0);}
		else {b.Insert(Playback.MoveXRecording.Last().Tick, 0); };
	if (Playback.MoveYRecording.IsEmpty()) { b.Insert(0, 1); } 
		else { b.Insert(Playback.MoveYRecording.Last().Tick, 1); };
	if (Playback.JumpRecording.IsEmpty()) { b.Insert(0, 2); } 
		else { b.Insert(Playback.JumpRecording.Last(), 2); }
	if (Playback.InteractRecording.IsEmpty()) { b.Insert(0, 3); } 
		else { b.Insert(Playback.InteractRecording.Last(), 3); };
	if (Playback.CameraRecording.IsEmpty()) { b.Insert(0, 4); } 
		else { b.Insert(Playback.CameraRecording.Last().Tick, 4); };

	// Compare each index and store the largest value
	for (float c : b){
		if (c > MaximumPlaybackTime) {
			MaximumPlaybackTime = c;
		}
	}

	// Setup two timers for this character - the playback tick and the total buff duration
	GetWorld()->GetTimerManager().SetTimer(PlaybackTickHandle, FTimerDelegate::CreateUObject(this, &ACharacter_Playback::PlaybackTick), TimerTickRate, true, TimerTickRate);
	GetWorld()->GetTimerManager().SetTimer(PlaybackTotalHandle, FTimerDelegate::CreateUObject(this, &ACharacter_Playback::EndPlayback), MaximumPlaybackTime, false, MaximumPlaybackTime);
}

void ACharacter_Playback::EndPlayback()
{
	// Clear the timer handles
	GetWorld()->GetTimerManager().ClearTimer(PlaybackTickHandle);
	GetWorld()->GetTimerManager().ClearTimer(PlaybackTotalHandle);
}

void ACharacter_Playback::PlaybackTick()
{
	// Check if MoveX[0].Tick == CurrentTick.  If so, call MoveX with the value and pop index 0
	if (!Playback.MoveXRecording.IsEmpty()) {
		if (Playback.MoveXRecording[0].Tick <= CurrentTickTime) { 
			MoveX(Playback.MoveXRecording[0].Value);
			Playback.MoveXRecording.RemoveAt(0);
		}
	}

	// Repeat for each input (also find a better way of doing this)
	if (!Playback.MoveYRecording.IsEmpty()) {
		if (Playback.MoveYRecording[0].Tick <= CurrentTickTime) {
			MoveY(Playback.MoveYRecording[0].Value);
			Playback.MoveYRecording.RemoveAt(0);
		}
	}

	if (!Playback.JumpRecording.IsEmpty()) {
		if (Playback.JumpRecording[0] <= CurrentTickTime) {
			Jump();
			Playback.JumpRecording.RemoveAt(0);
		}
	}

	if (!Playback.InteractRecording.IsEmpty()) {
		if (Playback.InteractRecording[0] <= CurrentTickTime) {
			Interact();
			Playback.InteractRecording.RemoveAt(0);
		}
	}

	if (!Playback.CameraRecording.IsEmpty()) {
		if (Playback.CameraRecording[0].Tick <= CurrentTickTime) {
			RotateCamera(Playback.CameraRecording[0].Value);
			Playback.CameraRecording.RemoveAt(0);
		}
	}

	// Finally, increment CurrentTickTime
	CurrentTickTime += TimerTickRate;
}
