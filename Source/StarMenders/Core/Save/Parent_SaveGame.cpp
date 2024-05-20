// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Save/Parent_SaveGame.h"

UParent_SaveGame::UParent_SaveGame()
{
}

UMaster_SaveGame::UMaster_SaveGame()
{
}

FSaveData::FSaveData()
{
}

FSaveData::FSaveData(int NewSaveID, FString NewSaveName, FName NewLastPlanet)
{
	SaveID = NewSaveID;
	SaveName = NewSaveName;
	LastPlanet = NewLastPlanet;
}
