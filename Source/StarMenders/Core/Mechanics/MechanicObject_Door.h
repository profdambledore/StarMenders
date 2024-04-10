// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Output.h"
#include "MechanicObject_Door.generated.h"

UCLASS()
class STARMENDERS_API AMechanicObject_Door : public AMechanicObject_Output
{
	GENERATED_BODY()
	
public:
	AMechanicObject_Door();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

};
