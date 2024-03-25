// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/RecordPad.h"

#include "Core/Character/Character_Record.h"
#include "Core/Character/Character_Default.h"
#include "Core/Level/LevelController.h"
#include "Core/Player/Controller_Player.h"

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

void ARecordPad::StartRecording(AController* PlayerController)
{
	if (PlayerController) {
		// Spawn a Character_Record
		ACharacter_Record* RecordingCharacter = GetWorld()->SpawnActor<ACharacter_Record>(RecordingCharacterClass, FVector(), FRotator());
		RecordingCharacter->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 95.0f));

		// Them make the inputted PlayerController possess this new character
		PlayerController->Possess(RecordingCharacter);

		// Finally, setup the character and start it's timer
		RecordingCharacter->StartRecording(this);
	}
}

void ARecordPad::OnRecorderBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter_Default::StaticClass())) {
		bPlayerOverlapping = true;
		Cast<ACharacter_Default>(OtherActor)->SetCurrentRecordPad(this);
		ToggleHologramVisibility();
	}
}

void ARecordPad::OnRecorderEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACharacter_Default::StaticClass())) {
		bPlayerOverlapping = false;
		Cast<ACharacter_Default>(OtherActor)->SetCurrentRecordPad(nullptr);
		ToggleHologramVisibility();
	}
}

void ARecordPad::ToggleHologramVisibility()
{
	if (!bPlayerOverlapping && RecordPresent) {
		RecorderCharacterHologram->SetVisibility(true, false);
	}
	else {
		RecorderCharacterHologram->SetVisibility(false, false);
	}
}

bool ARecordPad::GetHasRecording()
{
	return RecordPresent;
}

void ARecordPad::SetRecording(FRecordingData NewRecord, AController* PlayerController)
{
	Record = NewRecord;
	RecordPresent = true;

	// Cast to the controller and RePossess the original character
	AController_Player* PC = Cast<AController_Player>(PlayerController);
	PC->RePossessCharacter();
	PC->GetPawn()->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 95.0f));
}

void ARecordPad::ClearRecording()
{
	Record = FRecordingData();
	RecordPresent = false;
}
