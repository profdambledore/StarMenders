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

	/// -- Recorder Functions --
	// Called to start a recording on this recording pad
	void StartRecording(AController* PlayerController);

	/// -- Recorder Properties --
	// Called to get if the record pad has a recording
	bool GetHasRecording();

	// Called to set the recording on this pad
	void SetRecording(FRecordingData NewRecord, AController* PlayerController);

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

	/// -- Setup Functions --
	// Called to setup the visual elements of the record pad
	UFUNCTION(BlueprintImplementableEvent)
	void SetupVisualElements();

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
	/// -- Recorder Properties --
	// Int to denote the recorder's index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recorder Properties")
	int RecorderIndex = 0;

	// Bool to denote if the player is overlapping with this recorder
	bool bPlayerOverlapping = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recorder Properties")
	bool RecordPresent = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Record")
	FRecordingData Record;

	/// -- Colour Consts --
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Colour Consts")
	TMap<int, FColor> ColourConsts;



};
