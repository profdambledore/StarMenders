// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Level/LevelController.h"

#include "Core/Mechanics/RecordPad.h"
#include "Core/Character/Character_Default.h"
#include "Core/Level/Room_Parent.h"
#include "Core/Level/LevelDoor.h"
#include "Core/Mechanics/MechanicObject_Input.h"
#include "Core/Mechanics/MechanicObject_Output.h"

// Sets default values
ALevelController::ALevelController()
{
	// Setup Components
	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	LevelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Level Mesh"));
	LevelMesh->SetupAttachment(Root, "");

	// Get a reference to the level data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Core/Level/DT_LevelData"));
	if (DTObject.Succeeded()) { LevelDataTable = DTObject.Object; }

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();

	// Setup the portals
	ShipDoor->SetupPairedDoor(EntranceDoor);
	EntranceDoor->SetupPairedDoor(ShipDoor);
	ExitDoor->SetupPairedDoor(HiddenShipDoor);
	HiddenShipDoor->SetupPairedDoor(ExitDoor, ShipDoor);

	//SetupLevel(LevelID);
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelController::SetupLevel(FName InLevelID)
{
	ClearLevel();

	// Find the level from the data table
	FLevelData FoundRoom;
	FoundRoom = *LevelDataTable->FindRow<FLevelData>(InLevelID, "", true);

	if (FoundRoom.Name != "") {
		// First, update the entrance and exit portal locations
		EntranceDoor->SetActorTransform(FoundRoom.EntranceDoorTransform);
		EntranceDoor->AddActorWorldOffset(WorldLocationOffset);
		ExitDoor->SetActorTransform(FoundRoom.ExitDoorTransform);
		ExitDoor->AddActorWorldOffset(WorldLocationOffset);

		// Then update their clipping
		EntranceDoor->UpdateClipPlane();
		ExitDoor->UpdateClipPlane();

		// Add the output door to the OutputMechanics array
		// And setup the exit door with it's own output data
		OutputMechanics.Add(ExitDoor);
		ExitDoor->InputRequirement = FoundRoom.ExitDoorRequirements;
		ExitDoor->SetAlwaysActive();

		// Make some spawn info to make the object always spawn
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		// Next, spawn the required RecordPads
		for (FRecordPadData i : FoundRoom.RecordPads) {
			ARecordPad* NewPad = GetWorld()->SpawnActor<ARecordPad>(RecordPadClass, i.Transform, SpawnInfo);
			NewPad->AddActorWorldOffset(WorldLocationOffset);
			RecordPads.Add(NewPad);
			NewPad->SetupVisualElements(i.Index);
		}

		// Follow with the Output Mechanic Objects
		for (FOutputMechanicData j : FoundRoom.OutputMechanics) {
			AMechanicObject_Output* NewMechanic = GetWorld()->SpawnActor<AMechanicObject_Output>(j.Class, j.Transform, SpawnInfo);
			NewMechanic->AddActorWorldOffset(WorldLocationOffset);
			NewMechanic->ObjectName = j.ID;
			NewMechanic->InputRequirement = j.InputRequirements;
			NewMechanic->bOutputAlwaysActive = j.bOutputAlwaysActive;
			NewMechanic->ObjectToSpawn = j.ObjectToSpawn;
			NewMechanic->SetAlwaysActive();
			OutputMechanics.Add(NewMechanic);
		}

		// And the Input Mechanic Objects
		for (FInputMechanicData j : FoundRoom.InputMechanics) {
			AMechanicObject_Input* NewMechanic = GetWorld()->SpawnActor<AMechanicObject_Input>(j.Class, j.Transform, SpawnInfo);
			NewMechanic->AddActorWorldOffset(WorldLocationOffset);
			NewMechanic->ObjectName = j.ID;
			for (FName l : j.OutputIDs) {
				for (AMechanicObject_Output* m : OutputMechanics) {
					if (m->ObjectName == l) {
						NewMechanic->OutputsToObjects.Add(m);
					}
				}
			}

			InputMechanics.Add(NewMechanic);
		}

		// Set the level mesh
		LevelMesh->SetStaticMesh(FoundRoom.LevelMesh);
	}
	
}

void ALevelController::ClearLevel()
{
	// Check if a level is spawned.  If so, remove it
	// TO:DO - Update to not destroy stuff but store objects in pools
	if (LevelMesh->GetStaticMesh()) {
		LevelMesh->SetStaticMesh(nullptr);

		for (ARecordPad* RecordPad : RecordPads) {
			RecordPad->Destroy();
		}
		RecordPads.Empty();

		for (AMechanicObject_Input* input : InputMechanics) {
			input->Destroy();
		}
		InputMechanics.Empty();

		for (AMechanicObject_Output* output : OutputMechanics) {
			if (output->ObjectName != "OutputDoor") {
				output->Destroy();
			}
		}
		OutputMechanics.Empty();
	}
}

void ALevelController::StartLevelPlayback(ARecordPad* PadToRecordOn, ACharacter_Default* Character)
{
	// Check each stored record pad pointer matches the pointer inputted.  If so, start recording on that pad
	// Else, start that pads playback
	for (ARecordPad* i : RecordPads) {
		if (i == PadToRecordOn) {
			i->StartRecording(Character);
		}
		else {
			i->StartPlayback();
		}
	}

	// Next, reset the level mechanics
	for (AMechanicObject_Output* j : OutputMechanics) {
		j->ResetToDefault();
	}

	// Also, close the entrance door
	EntranceDoor->SetDoorState(false);
}

void ALevelController::EndLevelPlayback()
{
	for (ARecordPad* i : RecordPads) {
		i->EndPlayback();
	}

	// Also, reopen the entrance door
	EntranceDoor->SetDoorState(true);
}
