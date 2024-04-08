// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"

#include "LevelDoor.generated.h"

UENUM(BlueprintType, Category = "Mechanics")
enum EDoorType
{
	Ship UMETA(DisplayName = "Ship"),
	Entrance UMETA(DisplayName = "Entrance"),
	Exit UMETA(DisplayName = "Exit")
};


UCLASS()
class STARMENDERS_API ALevelDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelDoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to set the door to either closed or open
	void SetDoorState(bool bSetToClosed);

	UFUNCTION(BlueprintImplementableEvent)
	void SetupPairedDoor(ALevelDoor* DoorToPair, AActor* ActorToClip = nullptr);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap functions
	/// -- Button Overlap Events --
	UFUNCTION()
	void OnTZBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTZEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called to update the clip plane of the camera
	UFUNCTION(BlueprintCallable)
	void UpdateClipPlane();

	// Called to check if the item colliding with the TriggerZone should teleport to the paired door
	void GetShouldTeleport();

	// Called to check if a point on an object is crossing the portal
	bool GetIsCrossingPortal(FVector PointToCheck, FVector PortalLocation, FVector PortalNormal);

	// Called to teleport the character between this portal and the linked portal
	void TeleportCharacter(AActor* CharacterToTeleport);

	// Called to get the inverse rotation of a rotator
	FRotator GetInverseRotation(FRotator InRotator);

public:	
	// -- Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* TestObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Frame = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Plane = nullptr;

	// BoxCollision of the teleport activation zone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* TriggerZone = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneCaptureComponent2D* CaptureCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* CaptureSpringArm = nullptr;

protected:
	// Pointer to the door connected to this door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
	ALevelDoor* PairedDoor = nullptr;

	// Bool to denote if the door is open or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
	bool bDoorOpen = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actives")
	TEnumAsByte<EDoorType> DoorType;

	FVector LastPosition;
	bool bLastInFront;

	TArray<AActor*> TriggerZoneOverlaps;

private:
	
};
