// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/ChildActorComponent.h"

#include "Room_Parent.generated.h"

UCLASS()
class STARMENDERS_API ARoom_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoom_Parent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to setup the room's doors
	void SetupRoomDoors(class ALevelDoor* ShipDoor, ALevelDoor* HiddenShipDoor);

	// Called to setup the room's mechanics
	void SetupMechanics();

	// Called to return the RecordPad array
	TArray<class ARecordPad*> GetRecordPads();

	// Called to return the Mechanics array
	TArray<class AMechanicObject_Parent*> GetMechanicObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Room Objects --
	// Pointer to the EntranceDoor class, not the component
	class ALevelDoor* EntranceDoor = nullptr;

	// Pointer to the EntranceDoor class, not the component
	class ALevelDoor* ExitDoor = nullptr;

protected:
	/// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	// ChildActorComponent for the EntranceDoor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* EntranceDoorComponent = nullptr;

	// ChildActorComponent for the ExitDoor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UChildActorComponent* ExitDoorComponent = nullptr;

	// TArray of RecordPad pointers
	TArray<class ARecordPad*> RecordPads;

	int NextRecordPadIndex = 1;

	// TArray of Mechanic Objects
	TArray<class AMechanicObject_Parent*> MechanicObject;
};
