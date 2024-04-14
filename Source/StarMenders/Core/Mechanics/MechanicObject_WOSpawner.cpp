// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_WOSpawner.h"

AMechanicObject_WOSpawner::AMechanicObject_WOSpawner()
{
	ObjectSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Object Move Spawn Location"));
	ObjectSpawnLocation->SetupAttachment(Root, "");
}

void AMechanicObject_WOSpawner::ToggleOutput(bool bNowActive)
{
	// Check if bNowActive is true (we only want the box to move on activation)
	if (bNowActive == true) {
		// Check if LiveObject is set
		if (LiveObject) {
			// Move it to the ObjectSpawnLocation
			LiveObject->SetActorLocation(ObjectSpawnLocation->GetComponentLocation());
		}
		// If it isn't, spawn an object now
		else {
			LiveObject = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, ObjectSpawnLocation->GetComponentLocation(), ObjectSpawnLocation->GetComponentRotation());
		}
	}
	ModifyVisualElements(bNowActive);
}
