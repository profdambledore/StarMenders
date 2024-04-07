// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Level/LevelController.h"

#include "Core/Mechanics/RecordPad.h"
#include "Core/Character/Character_Parent.h"
#include "Core/Level/Room_Parent.h"
#include "Core/Level/LevelDoor.h"
#include "Core/Mechanics/MechanicObject_Parent.h"

// Sets default values
ALevelController::ALevelController()
{
	// Setup Components
	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Get a reference to the item data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Core/Level/DT_LevelData"));
	if (DTObject.Succeeded()) { LevelDataTable = DTObject.Object; }

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();

	SetupLevel("test_trees");
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelController::SetupLevel(FName InLevelID)
{
	// Find the level from the data table
	FLevelData FoundRoom;
	FoundRoom = *LevelDataTable->FindRow<FLevelData>(InLevelID, "", true);

	if (FoundRoom.Class) {
		// Get the class from the found struct and spawn it in the world
		ActiveRoom = GetWorld()->SpawnActor<ARoom_Parent>(FoundRoom.Class, FVector(0.0f, 1000.0f, 2000.0f), FRotator(0.0f, 40.0f, 0.0f));
		ActiveRoom->SetupRoomDoors(ShipDoor, HiddenShipDoor);
		ActiveRoom->SetupMechanics();
	}
	
}

void ALevelController::ClearLevel()
{
}

void ALevelController::StartLevelPlayback(ARecordPad* PadToRecordOn, ACharacter_Parent* Character)
{
	// Check each stored record pad pointer matches the pointer inputted.  If so, start recording on that pad
	// Else, start that pads playback
	for (ARecordPad* i : ActiveRoom->GetRecordPads()) {
		if (i == PadToRecordOn) {
			i->StartRecording(Character->GetController());
		}
		else {
			i->StartPlayback();
		}
	}

	// Next, reset the level mechanics
	for (AMechanicObject_Parent* j : ActiveRoom->GetMechanicObjects()) {
		j->ResetToDefault();
	}

	// Also, close the entrance door
	ActiveRoom->EntranceDoor->SetDoorState(false);
}

void ALevelController::EndLevelPlayback()
{
	for (ARecordPad* i : RecordPads) {
		i->EndPlayback();
	}

	// Also, reopen the entrance door
	ActiveRoom->EntranceDoor->SetDoorState(true);
}
