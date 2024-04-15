// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Level/LevelSelector.h"

#include "Kismet/GameplayStatics.h"

#include "Core/Level/LevelController.h"
#include "Core/Character/Character_Default.h"
#include "Core/Player/Controller_Player.h"

// Sets default values
ALevelSelector::ALevelSelector()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Setup the Player's Cameras
	TargetViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Target View Camera"));
	TargetViewCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	TargetViewCamera->SetupAttachment(Root, "");

	// Get a reference to the item data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Core/Level/DT_WorldMapData"));
	if (DTObject.Succeeded()) { WorldMapDataTable = DTObject.Object; }


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelSelector::BeginPlay()
{
	Super::BeginPlay();

	LevelController = Cast<ALevelController>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelController::StaticClass()));
	SetActiveSector("sec_tutorial");
	
}

// Called every frame
void ALevelSelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CharacterUsing) {
		// Fire a line trace infront of this camera
		FHitResult TraceHit;
		FCollisionQueryParams TraceParams;
		//TraceParams.AddIgnoredActor(this);

		// Mouse Location/Direction Vectors
		//FVector MouseDir, MouseLoc;

		// Get the player's mouse location in world space
		//CharacterUsing->PC->DeprojectMousePositionToWorld(MouseLoc, MouseDir);

		//bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseLoc, MouseLoc + 900, ECC_WorldDynamic, TraceParams);
		//DrawDebugLine(GetWorld(), MouseLoc + (MouseDir * 490), MouseLoc + (MouseDir * 500), FColor::Red, false, 5, 2, 5);
	}

}

void ALevelSelector::PrimaryInteract()
{
	// Fire a line trace infront of this camera
	FHitResult TraceHit;
	FCollisionQueryParams TraceParams;
	//TraceParams.AddIgnoredActor(this);

	// Mouse Location/Direction Vectors
	FVector MouseDir, MouseLoc;

	// Get the player's mouse location in world space
	CharacterUsing->PC->DeprojectMousePositionToWorld(MouseLoc, MouseDir);

	bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseLoc, MouseLoc + (MouseDir * 2000), ECC_WorldDynamic, TraceParams);
	DrawDebugLine(GetWorld(), MouseLoc + (MouseDir * 450), MouseLoc + (MouseDir * 2000), FColor::Green, true, 5, 0, 5);

	// Check if the trace hit a component.
	if (TraceHit.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Comp"));
		// Go through the array and find the component that matches the component hit
		for (FPlanetVisualData i : PlanetVisuals) {
			UE_LOG(LogTemp, Warning, TEXT("Testing Visual"));
			if (i.Mesh == TraceHit.GetComponent()) {
				// Call SetupLevel in the controller with the matching data
				LevelController->SetupLevel(i.LevelID);
			}
		}
	}
}

void ALevelSelector::SetActiveSector(FName SectorID)
{
	// First, check if we should go back to the world map
	if (SectorID == "WorldMap") {

	}
	else {
		// Find the sector in the data table
		FSectorData FoundSector;
		FoundSector = *WorldMapDataTable->FindRow<FSectorData>(SectorID, "", true);

		// Add enough to match the amount of planets needed
		if (FoundSector.PlanetIDs.Num() != PlanetVisuals.Num()) {
			AddNewPlanetVisual(FoundSector.PlanetIDs.Num());
		}

		// Next, setup each planet visual
		for (int i = 0; i < PlanetVisuals.Num(); i++) {
			// First, set the matching planet name
			PlanetVisuals[i].LevelID = FoundSector.PlanetIDs[i].PlanetID;

			// Next, setup the spring arm
			PlanetVisuals[i].SpringArm->TargetArmLength = FoundSector.PlanetIDs[i].Distance;

			// Follow with the static mesh 
			PlanetVisuals[i].Mesh->SetStaticMesh(FoundSector.PlanetIDs[i].Mesh);
			PlanetVisuals[i].Mesh->SetWorldScale3D(FVector(FoundSector.PlanetIDs[i].Scale));

			// Finally, setup the rotating movement component
			PlanetVisuals[i].Rotating->RotationRate = FRotator(0.0f, FoundSector.PlanetIDs[i].CentralRotationRate, 0.0f);
		}
	}
}

void ALevelSelector::SetActive(ACharacter_Default* NewInteractee)
{
	CharacterUsing = NewInteractee;
}

void ALevelSelector::EndInteraction()
{
	CharacterUsing->ExitInteraction();
	CharacterUsing = nullptr;
}

void ALevelSelector::AddNewPlanetVisual(int Target)
{
	int NewNumber = PlanetVisuals.Num() + 1;

	// Add a new spring arm
	USpringArmComponent* NewSpringArm = NewObject<USpringArmComponent>(this, FName(*FString::Printf(TEXT("Planet Spring Arm %i"), NewNumber)));
	NewSpringArm->RegisterComponent();
	NewSpringArm->bDoCollisionTest = false;
	NewSpringArm->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "");

	// Then a new static mesh component
	UStaticMeshComponent* NewMeshComp = NewObject<UStaticMeshComponent>(this, FName(*FString::Printf(TEXT("Planet Mesh %i"), NewNumber)));
	NewMeshComp->RegisterComponent();
	NewMeshComp->AttachToComponent(NewSpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "SpringEndpoint");

	// Finally, add a new rotational movement component
	URotatingMovementComponent* NewRotComp = NewObject<URotatingMovementComponent>(this, FName(*FString::Printf(TEXT("Planet Rot Comp %i"), NewNumber)));
	NewRotComp->RegisterComponent();
	NewRotComp->SetUpdatedComponent(NewSpringArm);

	// Add it to the array
	PlanetVisuals.Add(FPlanetVisualData(NewMeshComp, NewSpringArm, NewRotComp));

	// Check if there is now enough component sets added.  If not, recurse
	if (PlanetVisuals.Num() != Target) {
		AddNewPlanetVisual(Target);
	}
}

