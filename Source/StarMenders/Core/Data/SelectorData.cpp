// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Data/SelectorData.h"


FSectorData::FSectorData()
{
}

FSectorData::~FSectorData()
{
}

FPlanetData::FPlanetData()
{
}

FPlanetData::~FPlanetData()
{
}

FPlanetVisualData::FPlanetVisualData()
{
}

FPlanetVisualData::FPlanetVisualData(UStaticMeshComponent* NewMesh, USpringArmComponent* NewSpringArm, URotatingMovementComponent* NewRotating, FName NewLevelID)
{
	Mesh = NewMesh;
	SpringArm = NewSpringArm;
	Rotating = NewRotating;
	LevelID = NewLevelID;
}

void FPlanetVisualData::UpdateLevelID(FName NewLevelID)
{
	LevelID = NewLevelID;
}

FPlanetVisualData::~FPlanetVisualData()
{
}
