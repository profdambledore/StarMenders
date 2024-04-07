// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Level/Room_Parent.h"

#include "Core/Level/LevelDoor.h"
#include "Core/Mechanics/RecordPad.h"
#include "Core/Mechanics/MechanicObject_Parent.h"

// Sets default values
ARoom_Parent::ARoom_Parent()
{
	// Setup Components
	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	// Doors
	EntranceDoorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Entrance Door Component"));
	EntranceDoorComponent->SetupAttachment(Root, "");

	ExitDoorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Exit Door Component"));
	ExitDoorComponent->SetupAttachment(Root, "");

	// Get the BP_LevelDoor class
	static ConstructorHelpers::FClassFinder<ALevelDoor>DoorClass(TEXT("/Game/Core/Level/BP_LevelDoor"));
	if (DoorClass.Succeeded()) {
		EntranceDoorComponent->SetChildActorClass(DoorClass.Class.Get());
		ExitDoorComponent->SetChildActorClass(DoorClass.Class.Get());
	};

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARoom_Parent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoom_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom_Parent::SetupRoomDoors(ALevelDoor* ShipDoor, ALevelDoor* HiddenShipDoor)
{
	// Check that the door classes have been set up correctly
	if (EntranceDoorComponent->GetChildActor()) {
		// If so, store their pointers
		EntranceDoor = Cast<ALevelDoor>(EntranceDoorComponent->GetChildActor());
		ExitDoor = Cast<ALevelDoor>(ExitDoorComponent->GetChildActor());

		// Then setup the doors
		ShipDoor->SetupPairedDoor(EntranceDoor);
		EntranceDoor->SetupPairedDoor(ShipDoor);
		ExitDoor->SetupPairedDoor(HiddenShipDoor);
		HiddenShipDoor->SetupPairedDoor(ExitDoor, ShipDoor);
	}
}

void ARoom_Parent::SetupMechanics()
{
	// Get all ChildActorComponents
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors, false);

	// Then sort them into arrays based on what class they are
	for (AActor* i : ChildActors) {
		if (i->IsA(ARecordPad::StaticClass())) {
			RecordPads.Add(Cast<ARecordPad>(i));
			RecordPads[RecordPads.Num() - 1]->SetupVisualElements(NextRecordPadIndex);
			NextRecordPadIndex++;
		}
		else if (i->IsA(AMechanicObject_Parent::StaticClass())) {
			MechanicObject.Add(Cast<AMechanicObject_Parent>(i));
		}
	}
}

TArray<class ARecordPad*> ARoom_Parent::GetRecordPads()
{
	return RecordPads;
}

TArray<class AMechanicObject_Parent*> ARoom_Parent::GetMechanicObjects()
{
	return MechanicObject;
}

