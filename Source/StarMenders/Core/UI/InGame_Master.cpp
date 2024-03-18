// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/InGame_Master.h"

#include "Core/UI/InGame_Default.h"
#include "Core/Character/Character_Parent.h"

void UInGame_Master::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInGame_Master::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UInGame_Master::SetPlayerOwner(ACharacter_Parent* NewOwner)
{
	Player = NewOwner;

	// Also setup the states with a pointer to this master
	DefaultState->MasterUI = this;
}

ACharacter_Parent* UInGame_Master::GetPlayerOwner()
{
	return Player;
}


