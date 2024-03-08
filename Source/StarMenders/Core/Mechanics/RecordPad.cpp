// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/RecordPad.h"
#include "Core/Character/Character_Parent.h"
#include "Core/Level/LevelController.h"

// Sets default values
ARecordPad::ARecordPad()
{
	// Setup Components
	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Setup the recorder outer mesh
	RecorderOuterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Recorder Outer Mesh"));
	RecorderOuterMesh->SetupAttachment(Root, "");

	// Setup the recorder hologram mesh
	RecorderCharacterHologram = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Recorder Character Hologram Mesh"));
	RecorderCharacterHologram->SetupAttachment(Root, "");

	// Setup the button trigger zone
	RecorderTriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Recorder Trigger Zone"));
	RecorderTriggerZone->SetupAttachment(Root, "");

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARecordPad::BeginPlay()
{
	Super::BeginPlay();

	// Update the state of the Hologram
	ToggleHologramVisibility();

	SetupVisualElements();

	// Add the overlap events to the ButtonTriggerZone
	// Add Overlap Events
	RecorderTriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ARecordPad::OnRecorderBeginOverlap);
	RecorderTriggerZone->OnComponentEndOverlap.AddDynamic(this, &ARecordPad::OnRecorderEndOverlap);
	
}

// Called every frame
void ARecordPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARecordPad::OnRecorderBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter_Parent::StaticClass())) {
		bPlayerOverlapping = true;
		Cast<ACharacter_Parent>(OtherActor)->SetCurrentRecordPad(this);
		ToggleHologramVisibility();
	}
}

void ARecordPad::OnRecorderEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACharacter_Parent::StaticClass())) {
		bPlayerOverlapping = false;
		Cast<ACharacter_Parent>(OtherActor)->SetCurrentRecordPad(nullptr);
		ToggleHologramVisibility();
	}
}

void ARecordPad::ToggleHologramVisibility()
{
	if (!bPlayerOverlapping && TEMP_RecordPresent) {
		RecorderCharacterHologram->SetVisibility(true, false);
	}
	else {
		RecorderCharacterHologram->SetVisibility(false, false);
	}
}

bool ARecordPad::GetHasRecording()
{
	return TEMP_RecordPresent;
}
