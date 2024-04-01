// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Level/LevelController.h"

#include "Core/Mechanics/RecordPad.h"
#include "Core/Character/Character_Parent.h"

// Sets default values
ALevelController::ALevelController()
{
	// Setup Components
	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelController::SetupLevel()
{
	// Find all record pads 
}

void ALevelController::StartLevelPlayback(ARecordPad* PadToRecordOn, ACharacter_Parent* Character)
{
	// Check each stored record pad pointer matches the pointer inputted.  If so, start recording on that pad
	// Else, start that pads playback
	for (ARecordPad* i : RecordPads) {
		if (i == PadToRecordOn) {
			i->StartRecording(Character->GetController());
		}
		else {
			i->StartPlayback();
		}
	}
}

void ALevelController::EndLevelPlayback()
{
	for (ARecordPad* i : RecordPads) {
		i->EndPlayback();
	}
}
