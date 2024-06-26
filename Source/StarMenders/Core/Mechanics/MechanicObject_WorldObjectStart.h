// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Output.h"
#include "MechanicObject_WorldObjectStart.generated.h"

UCLASS()
class STARMENDERS_API AMechanicObject_WorldObjectStart : public AMechanicObject_Output
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ResetToDefault() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	AActor* LiveObject = nullptr;
	
};
