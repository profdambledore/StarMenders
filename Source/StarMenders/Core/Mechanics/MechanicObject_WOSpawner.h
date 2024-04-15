// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Output.h"
#include "MechanicObject_WOSpawner.generated.h"


UCLASS()
class STARMENDERS_API AMechanicObject_WOSpawner : public AMechanicObject_Output
{
	GENERATED_BODY()

public:
	AMechanicObject_WOSpawner();

	// Called when InputCount >= InputRequirement
	virtual void ToggleOutput(bool bNowActive);

	virtual void ResetToDefault() override;

public:
	/// -- Components --
	// SceneComponent of the object spawn/move location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* ObjectSpawnLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	AActor* LiveObject = nullptr;
};
