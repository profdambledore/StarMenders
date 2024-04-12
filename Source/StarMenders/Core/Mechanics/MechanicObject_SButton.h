// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Input.h"
#include "MechanicObject_SButton.generated.h"

/**
 * 
 */
UCLASS()
class STARMENDERS_API AMechanicObject_SButton : public AMechanicObject_Input
{
	GENERATED_BODY()

public:
	AMechanicObject_SButton();

	// Called by the player to press down on the button
	void UseButton();
	
};
