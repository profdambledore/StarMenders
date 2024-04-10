// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_Door.h"

AMechanicObject_Door::AMechanicObject_Door()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMechanicObject_Door::BeginPlay()
{
	Super::BeginPlay();
}


void AMechanicObject_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
