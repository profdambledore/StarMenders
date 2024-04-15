// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "SelectorData.generated.h"

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FPlanetData
{
public:
	GENERATED_BODY();

	// The ID of the planet data of this level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	FName PlanetID;

	// The static mesh of the planet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	UStaticMesh* Mesh = nullptr;

	// The rotation rate of the planet on it's axis
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	float AxisRotationRate;

	// The rotation rate of the planet around the central star
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	float CentralRotationRate;

	// The distance of the planet from the central star (the spring arm's length)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	float Distance;

	// The relative starting rotation based on the current time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	float RelativeStartingRotation;

	// The scale of the planet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	float Scale;

	// The colour of the planet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet Data")
	FColor Colour;

public:
	FPlanetData();
	~FPlanetData();
};

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FSectorData : public FTableRowBase
{
public:
	GENERATED_BODY();

	// The name of the sector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sector Data")
	FName SectorID;

	// The planets which are contained in this sector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sector Data")
	TArray<FPlanetData> PlanetIDs;

public:
	FSectorData();
	~FSectorData();
};

USTRUCT(BlueprintType, Category = "Levels")
struct STARMENDERS_API FPlanetVisualData
{
public:
	GENERATED_BODY();

	// The planet mesh component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sector Data")
	UStaticMeshComponent* Mesh;

	// The planet spring arm component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sector Data")
	USpringArmComponent* SpringArm;

	// The planet rotation component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sector Data")
	URotatingMovementComponent* Rotating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sector Data")
	FName LevelID;

public:
	FPlanetVisualData();
	FPlanetVisualData(UStaticMeshComponent* NewMesh, USpringArmComponent* NewSpringArm, URotatingMovementComponent* NewRotating, FName NewLevelID = "");
	void UpdateLevelID(FName NewLevelID);
	~FPlanetVisualData();
};