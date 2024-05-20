// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Parent_SaveGame.generated.h"

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FSaveData
{
public:
	GENERATED_BODY();

	FSaveData();
	FSaveData(int NewSaveID, FString NewSaveName, FName NewLastPlanet);

public:
	// The ID of the save
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
	int SaveID;

	// The name of the matching save
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
	FString SaveName = "";

	// The last planet visited on this save
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Data")
	FName LastPlanet = "";
};

UCLASS()
class STARMENDERS_API UParent_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UParent_SaveGame();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Data")
	int SaveSlotID = -1;

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Data")
	float TotalTimePlayed = 0.0f;

	// TMap of any unlocked planets, as well as the planets best time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Data")
	TMap<FName, float> UnlockedPlanets;

	// Name of the last planet visited
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Data")
	FName LastSectorVisited;
};

UCLASS()
class STARMENDERS_API UMaster_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMaster_SaveGame();

public:
	// TMap of all known savegames
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Data")
	TArray<FSaveData> SaveGames;

};
