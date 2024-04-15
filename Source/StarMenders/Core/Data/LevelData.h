// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "LevelData.generated.h"

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FRecordPadData
{
public:
	GENERATED_BODY();

	// The index of this record pad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record Pad Data")
	int Index = -1;

	// The transform of the record pad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record Pad Data")
	FTransform Transform;

public:
	FRecordPadData();
	~FRecordPadData();
};

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FInputMechanicData
{
public:
	GENERATED_BODY();

	// The ID of this mechanic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	FName ID;

	// The transform of the mechanic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	FTransform Transform;

	// The class of the mechanic object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	TSubclassOf<class AMechanicObject_Input> Class;

	// The ID's of this mechanic's output object (if there is any)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	TArray<FName> OutputIDs;

public:
	FInputMechanicData();
	~FInputMechanicData();
};

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FOutputMechanicData
{
public:
	GENERATED_BODY();

	// The ID of this mechanic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	FName ID;

	// The transform of the mechanic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	FTransform Transform;

	// The class of the mechanic object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	TSubclassOf<class AMechanicObject_Output> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	int InputRequirements = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	bool bOutputAlwaysActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	TSubclassOf<AActor> ObjectToSpawn = nullptr;

public:
	FOutputMechanicData();
	~FOutputMechanicData();
};

// Struct holding the data of an input float recording
USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FLevelData : public FTableRowBase
{
public:
	GENERATED_BODY();

	/// -- Level Data --
	// The name of the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	FName Name;

	// The static mesh of the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	UStaticMesh* LevelMesh = nullptr;

	/// -- Portal Door Data --
	// The transform of the entrance door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Door Data")
	FTransform EntranceDoorTransform;

	// The transform of the exit door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Door Data")
	FTransform ExitDoorTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Door Data")
	int ExitDoorRequirements = 0;

	/// -- Record Pad Data --
	// TArray of all record pads in the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Record Pad Data")
	TArray<FRecordPadData> RecordPads;

	/// -- Mechanic Data --
	// TArray of all record pads in the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	TArray<FInputMechanicData> InputMechanics;

	// TArray of all record pads in the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Data")
	TArray<FOutputMechanicData> OutputMechanics;

public:
	FLevelData();
	~FLevelData();
};