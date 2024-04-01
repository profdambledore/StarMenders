// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/Character_Parent.h"

#include "Core/Data/RecordingData.h"

#include "Character_Playback.generated.h"

UCLASS()
class STARMENDERS_API ACharacter_Playback : public ACharacter_Parent
{
	GENERATED_BODY()

public:
	void SetupPlayback(FRecordingData NewPlayback);

	// Called to start a recording
	void StartPlayback();

	// Timer event for the total duration of the recording
	void EndPlayback();

	virtual void MoveX(float AxisValue) override;

	virtual void RotateCamera(FVector2D AxisValue) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Timer event for each tick of the playback
	void PlaybackTick();

protected:
	// Timer handle for the recording tick
	FTimerHandle PlaybackTickHandle;

	// Timer handle for the total recording time
	FTimerHandle PlaybackTotalHandle;

	// Float denoting the maximum time allowed to record
	float MaximumPlaybackTime = 0.0f;

	// Float denoting the current tick time
	float CurrentTickTime = 0.0f;

	// Record struct holding all data about the record
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Record")
	FRecordingData Playback;	

	// Record struct holding all data about the record
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Record")
	FRecordingData TEMP_Playback;

private:
	class APlayerController* PC = nullptr;
};
