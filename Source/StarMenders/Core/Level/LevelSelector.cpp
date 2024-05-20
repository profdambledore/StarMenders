// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Level/LevelSelector.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Core/Level/LevelController.h"
#include "Core/Character/Character_Default.h"
#include "Core/Player/Controller_Player.h"
#include "Core/UI/LevelSelect_Master.h"

// Sets default values
ALevelSelector::ALevelSelector()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Setup the Player's Cameras
	TargetViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Target View Camera"));
	TargetViewCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	TargetViewCamera->SetupAttachment(Root, "");

	// Next, setup the SelectorWidget
	SelectorWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Selector Widget Component"));
	SelectorWidgetComponent->SetupAttachment(Root, "");

	// Get a reference to the planet and sector data table
	ConstructorHelpers::FObjectFinder<UDataTable>DTObject(TEXT("/Game/Core/Level/DT_SectorData"));
	if (DTObject.Succeeded()) { SectorDataTable = DTObject.Object; }

	ConstructorHelpers::FObjectFinder<UDataTable>PDTObject(TEXT("/Game/Core/Level/DT_PlanetData"));
	if (PDTObject.Succeeded()) { PlanetDataTable = PDTObject.Object; }

	// Get the LevelSelect UserWidget for the character and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Core/UI/WBP_LevelSelector"));
	if (UIClass.Succeeded()) {
		SelectorWidgetComponent->SetWidgetClass(UIClass.Class);
	};


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelSelector::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the interact widget class
	SelectorUI = Cast<ULevelSelect_Master>(SelectorWidgetComponent->GetWidget());

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
		FVector MouseDir, MouseLoc;

		// Get the player's mouse location in world space
		CharacterUsing->PC->DeprojectMousePositionToWorld(MouseLoc, MouseDir);

		bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, MouseLoc, MouseLoc + (MouseDir * 2000), ECC_WorldDynamic, TraceParams);
		//DrawDebugLine(GetWorld(), MouseLoc + (MouseDir * 490), MouseLoc + (MouseDir * 500), FColor::Red, false, 5, 2, 5);

		// Check if the trace hit a component.
		if (TraceHit.GetActor() == this) {
			UE_LOG(LogTemp, Warning, TEXT("Hit Comp"));
			// Go through the array and find the component that matches the component hit
			for (FPlanetVisualData i : PlanetVisuals) {
				if (i.Mesh == TraceHit.GetComponent()) {
					if (!SelectorWidgetComponent->IsVisible()) {
						SelectorWidgetComponent->SetVisibility(true, true);
					}

					if (LevelController->GetLevelUnlocked(i.LevelID)) {
						FPlanetData NewPlanet = GetPlanetData(i.LevelID);
						SelectorUI->UpdateWidgetData(NewPlanet.PlanetName, NewPlanet.Tagline);
					}
					else {
						SelectorUI->UpdateWidgetData("???", "???");
					}

					SelectorWidgetComponent->SetWorldLocation(i.Mesh->GetComponentLocation());
					SelectorWidgetComponent->AddLocalOffset(FVector(0.0f, 0.0f, -50.0f));
					SelectorWidgetComponent->SetRelativeRotation(UKismetMathLibrary::FindLookAtRotation(SelectorWidgetComponent->GetComponentLocation(), TargetViewCamera->GetComponentLocation()));
				}
			}
		}
		else {
			if (SelectorWidgetComponent->IsVisible()) {
				SelectorWidgetComponent->SetVisibility(false, true);
			}
		}
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
				// Check if the level is unlocked
				if (LevelController->GetLevelUnlocked(i.LevelID)) {
					// Call SetupLevel in the controller with the matching data
					LevelController->SetupLevel(GetPlanetData(i.LevelID).LevelID);
				}
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
		FoundSector = *SectorDataTable->FindRow<FSectorData>(SectorID, "", true);

		// Add enough to match the amount of planets needed
		if (FoundSector.PlanetIDs.Num() != PlanetVisuals.Num()) {
			AddNewPlanetVisual(FoundSector.PlanetIDs.Num());
		}

		// Next, setup each planet visual
		for (int i = 0; i < PlanetVisuals.Num(); i++) {
			// First, set the matching planet name
			PlanetVisuals[i].LevelID = FoundSector.PlanetIDs[i];

			// Next, find the PlanetData from the PlanetDataTable
			FPlanetData NewPlanet = GetPlanetData(FoundSector.PlanetIDs[i]);

			// Next, setup the spring arm
			PlanetVisuals[i].SpringArm->TargetArmLength = NewPlanet.Distance;

			// Follow with the static mesh 
			PlanetVisuals[i].Mesh->SetStaticMesh(NewPlanet.Mesh);
			PlanetVisuals[i].Mesh->SetWorldScale3D(FVector(NewPlanet.Scale));

			// Finally, setup the rotating movement component
			PlanetVisuals[i].Rotating->RotationRate = FRotator(0.0f, NewPlanet.CentralRotationRate, 0.0f);
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

FPlanetData ALevelSelector::GetPlanetData(FName PlanetID)
{
	return *PlanetDataTable->FindRow<FPlanetData>(PlanetID, "", true);
}

