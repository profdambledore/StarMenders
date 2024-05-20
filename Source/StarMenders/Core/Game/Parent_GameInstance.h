// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Parent_GameInstance.generated.h"

UCLASS()
class STARMENDERS_API UParent_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// FString denoting the sector that needs to be loaded
	FString SectorToLoad = "";

	// FString denoting the current Save Game Slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Saving and Loading")
	FString CurrentSaveName = "Testing";

	// TMap denoting all planets currently unlocked on load
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loaded Data")
	TMap<FName, float> Load_UnlockedPlanets;
};
