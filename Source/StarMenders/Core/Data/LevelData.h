// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "LevelData.generated.h"

// Struct holding the data of an input float recording
USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FLevelData : public FTableRowBase
{
public:
	GENERATED_BODY();

	/// -- Level Data --
	// The name of the level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	float Name;

	// The class of the leve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	TSubclassOf<class ARoom_Parent> Class;

public:
	FLevelData();
	
	~FLevelData();
};
