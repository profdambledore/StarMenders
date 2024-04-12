// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Parent.h"
#include "MechanicObject_Input.generated.h"

/**
 * 
 */
UCLASS()
class STARMENDERS_API AMechanicObject_Input : public AMechanicObject_Parent
{
	GENERATED_BODY()

public:
	/// -- Mechanic Functions - Inputs --
	// Called to toggle the input object on or off
	UFUNCTION(BlueprintCallable)
	void ToggleInputActive();

public:
	/// -- Mechanic Properties - Input --
	// Boolean denoting if this input is currently active
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Properties")
	bool bInputActive = false;

	// TArray of pointers to other MechanicObjects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Properties")
	TArray<class AMechanicObject_Output*> OutputsToObjects;
};
