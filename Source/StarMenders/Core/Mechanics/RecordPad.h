// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Core/Data/RecordingData.h"

#include "RecordPad.generated.h"

UCLASS()
class STARMENDERS_API ARecordPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecordPad();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Recording Functions --
	// Called to start a recording on this recording pad
	void StartRecording(class ACharacter_Default* PlayerCharacter);

	// Called to clear the recording on the pad
	void ClearRecording();

	/// -- Record Properties --
	// Called to get if the record pad has a recording
	bool GetHasRecording();

	// Called to set the recording on this pad
	void SetRecording(FRecordingData NewRecord, ACharacter_Default* PlayerCharacter);

	/// -- Playback Functions --
	// Called to start the playback of the recording (if one exists)
	void StartPlayback();
	
	// Called to end the playback of the recording
	void EndPlayback();

	/// -- Setup Functions --
	// Called to setup the visual elements of the record pad
	UFUNCTION(BlueprintImplementableEvent)
	void SetupVisualElements(int Index);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Button Overlap Events --
	UFUNCTION()
	void OnRecorderBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnRecorderEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// -- Hologram Funtion --
	// Called to modify if the hologram should be shown or not
	void ToggleHologramVisibility();

public:	
	/// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	// StaticMesh of the recorder outer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* RecorderOuterMesh = nullptr;

	// SkeletalMesh of the character hologram when a recording is present
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* RecorderCharacterHologram = nullptr;

	// BoxCollision of the recorder activation zone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* RecorderTriggerZone = nullptr;

protected:
	/// -- Character Properties --
	// Pointer to the recording character class blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Properties")
	TSubclassOf<class ACharacter_Record> RecordingCharacterClass = nullptr;

	// Pointer to the playback character class blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Properties")
	TSubclassOf<class ACharacter_Playback> PlaybackCharacterClass = nullptr;

	/// -- Actives --
	// Int to denote the recorder's index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
	int RecorderIndex = 0;

	// Bool to denote if the player is overlapping with this recorder
	bool bPlayerOverlapping = false;

	// Bool to denote if a record exists
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
	bool RecordPresent = false;

	// Pointer to the current spawned character associated with this pad
	class ACharacter_Parent* CurrentCharacter = nullptr;

	// Record struct holding all data about the record
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Record")
	FRecordingData Record;

	/// -- Colour Consts --
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Colour Consts")
	TMap<int, FColor> ColourConsts;
};
