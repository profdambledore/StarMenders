// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "Mechanic_WorldObject.generated.h"

UCLASS()
class STARMENDERS_API AMechanic_WorldObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMechanic_WorldObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to return the character currently grabbing the pickup
	class ACharacter_Parent* GetCurrentGrabber();

	void SetCurrentGrabber(class ACharacter_Parent* NewGrabber);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ObjectMesh = nullptr;

	/// -- Actives --
	// Pointer to the character currently grabbing this object
	class ACharacter_Parent* CurrentGrabber = nullptr;

};
