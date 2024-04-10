// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_Input.h"
#include "Core/Mechanics/MechanicObject_Output.h"

void AMechanicObject_Input::ToggleInputActive()
{
	bInputActive = !bInputActive;

	// Add inputs to all output objects
	for (AMechanicObject_Output* i : OutputsToObjects) {
		i->IncreaseInputAmount(bInputActive);
	}
}
