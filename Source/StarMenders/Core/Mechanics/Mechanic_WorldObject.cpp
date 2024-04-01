// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/Mechanic_WorldObject.h"

#include "Core/Character/Character_Parent.h"

// Sets default values
AMechanic_WorldObject::AMechanic_WorldObject()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	ObjectMesh->SetupAttachment(Root, "");

	// Setup the character's gameplay tags
	Tags.Add("CanActivateButtons"); // Allows the character to activate buttons
	Tags.Add("CanBePickedUp"); // Allows the character to activate buttons

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMechanic_WorldObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMechanic_WorldObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ACharacter_Parent* AMechanic_WorldObject::GetCurrentGrabber()
{
	return CurrentGrabber;
}

void AMechanic_WorldObject::SetCurrentGrabber(ACharacter_Parent* NewGrabber)
{
	CurrentGrabber = NewGrabber;
}

