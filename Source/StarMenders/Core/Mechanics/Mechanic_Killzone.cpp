// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/Mechanic_Killzone.h"

// Sets default values
AMechanic_Killzone::AMechanic_Killzone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMechanic_Killzone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMechanic_Killzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

