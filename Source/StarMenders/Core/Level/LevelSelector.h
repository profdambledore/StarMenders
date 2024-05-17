// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "Core/Data/SelectorData.h"

#include "LevelSelector.generated.h"

UCLASS()
class STARMENDERS_API ALevelSelector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSelector();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called by the interacting player to primary interact with the selector
	void PrimaryInteract();

	// Called by
	void SetActiveSector(FName SectorID);

	// Called by the interacting player
	void SetActive(class ACharacter_Default* NewInteractee);

	// Called by the interacting player or this object to stop the character interacting
	void EndInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AddNewPlanetVisual(int Target);

	FPlanetData GetPlanetData(FName PlanetID);

public:	
	/// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	// CameraComponent of the level selector's target view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* TargetViewCamera = nullptr;

	// WidgetComponent used to display the InGame UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* SelectorWidgetComponent;

	// TArray of additional components added after initialization
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<FPlanetVisualData> PlanetVisuals;

	/// -- Actives --
	// Bool to denote if the Level Selector is currently in use
	bool bCurrentlyInUse = false;

	/// -- Data Table Pointers --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* SectorDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UDataTable* PlanetDataTable = nullptr;

protected:
	/// -- Pointers --
	// Pointer to the LevelController in the world
	class ALevelController* LevelController = nullptr;

	// Pointer to the character using this LevelSelector
	class ACharacter_Default* CharacterUsing = nullptr;

	// Pointer to the UI class in the WidgetComponent
	class ULevelSelect_Master* SelectorUI = nullptr;
};
