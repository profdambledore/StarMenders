// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_Parent.h"

// Sets default values
AMechanicObject_Parent::AMechanicObject_Parent()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMechanicObject_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMechanicObject_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMechanicObject_Parent::StartTrigger()
{
}

void AMechanicObject_Parent::EndTrigger()
{
}