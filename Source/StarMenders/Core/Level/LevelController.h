// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelController.generated.h"

UCLASS()
class STARMENDERS_API ALevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Recording and Playing --
	// Called to update the Player's UI with the information about a record pad
	// Will be cleared if RecordPadOverlapping is nullptr
	void UpdatePlayerUIElements(class ARecordPad* RecordPadOverlapping);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

private:
	/// -- Pointers --
	// Pointer to the player's character
	class ACharacter_Parent* Player = nullptr;

};
