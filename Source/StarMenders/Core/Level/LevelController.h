// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Core/Data/LevelData.h"

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
	void SetupLevel(FName InLevelID);

	// Called to clear the current level
	void ClearLevel();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	FName LevelID;

	/// -- Pointers --
	// Pointer to the player's character
	class ACharacter_Parent* Player = nullptr;

	// Pointer to the ship door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	class ALevelDoor* ShipDoor = nullptr;

	// Pointer to the hidden ship door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	class ALevelDoor* HiddenShipDoor = nullptr;

	// Pointer array to all RecordPads
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	TArray<class ARecordPad*> RecordPads;

	// Pointer to the Parent_Room
	class ARoom_Parent* ActiveRoom = nullptr;

protected:
	// Data Table of all levels
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* LevelDataTable = nullptr;

private:

};
