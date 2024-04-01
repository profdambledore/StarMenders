// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelController.generated.h"

UCLASS()
class STARMENDERS_API ALevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Setup --
	// Called to setup a new level
	void SetupLevel();

	/// -- Recording and Playing --
	// Called to start playback of a level and record on a selected pad
	void StartLevelPlayback(ARecordPad* PadToRecordOn, ACharacter_Parent* Character);

	// Called to end the playback of a level
	void EndLevelPlayback();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	/// -- Pointers --
	// Pointer to the player's character
	class ACharacter_Parent* Player = nullptr;

	// Pointer array to all RecordPads
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	TArray<class ARecordPad*> RecordPads;

private:

};
