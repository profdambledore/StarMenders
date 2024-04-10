// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Core/Data/LevelData.h"

#include "Components/StaticMeshComponent.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* LevelMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	FName LevelID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Testing")
	FVector WorldLocationOffset;

	/// -- Pointers --
	// Pointer to the player's character
	class ACharacter_Parent* Player = nullptr;

	/// -- Portal Doors --
	// Pointer to the ship door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portals")
	class ALevelDoor* ShipDoor = nullptr;

	// Pointer to the hidden ship door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portals")
	class ALevelDoor* HiddenShipDoor = nullptr;

	// Pointer to the entrance level door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portals")
	class ALevelDoor* EntranceDoor = nullptr;

	// Pointer to the entrance level door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portals")
	class ALevelDoor* ExitDoor = nullptr;

	/// -- Level Assets --
	// Pointer array to all RecordPads
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	TArray<class ARecordPad*> RecordPads;

	// Pointer map to all Input Mechanic Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	TArray<class AMechanicObject_Input*> InputMechanics;

	// Pointer map to all Output Mechanic Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Assets")
	TArray<class AMechanicObject_Output*> OutputMechanics;

	// -- Classes --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes")
	TSubclassOf<class ARecordPad> RecordPadClass;

protected:
	// Data Table of all levels
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* LevelDataTable = nullptr;

private:

};
