// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Input.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "MechanicObject_Button.generated.h"

UCLASS()
class STARMENDERS_API AMechanicObject_Button : public AMechanicObject_Input
{
	GENERATED_BODY()
	
public:
	AMechanicObject_Button();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Button Overlap Events --
	UFUNCTION()
	void OnButtonBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnButtonEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/// -- Components --
	// StaticMesh of the button outer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ButtonOuterMesh = nullptr;

	// StaticMesh of the button inner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ButtonInnerMesh = nullptr;

	// BoxCollision of the button activation zone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* ButtonTriggerZone = nullptr;

protected:
	// TArray of pointers to actors currently overlapping with this button
	TArray<AActor*> OverlapActors;
};
