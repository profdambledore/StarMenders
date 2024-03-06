// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Parent.h"
#include "MechanicObject_Door.generated.h"

UCLASS()
class STARMENDERS_API AMechanicObject_Door : public AMechanicObject_Parent
{
	GENERATED_BODY()
	
public:
	AMechanicObject_Door();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Trigger Function --
	// Called when this object recieves it's input
	virtual void StartTrigger() override;

	// Called when this object stops recieving it's input
	virtual void EndTrigger() override;

	// Called when this object stops recieving it's input
	virtual void ActivateObject(bool bPositive) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/// -- Components --
};
