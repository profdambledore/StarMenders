// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_WorldObjectStart.h"

void AMechanicObject_WorldObjectStart::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the object that the class has 
	LiveObject = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, GetActorLocation(), GetActorRotation());
}

void AMechanicObject_WorldObjectStart::ResetToDefault()
{
	if (LiveObject) {
		LiveObject->SetActorLocation(FVector());
		LiveObject->SetActorRotation(this->GetActorRotation());
	}
	else {
		LiveObject = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, GetActorLocation(), GetActorRotation());
	}
}
