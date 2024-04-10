// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_Output.h"

void AMechanicObject_Output::IncreaseInputAmount(bool bPositive)
{
	// Start by increasing this outputs current InputCount
	if (bPositive) {
		InputCount++;
	}
	else {
		InputCount--;
	}

	// Then check if the output has reached its InputRequirements
	if (InputCount >= InputRequirement) {
		ToggleOutput(true);
	}
	else {
		ToggleOutput(false);
	}
}

void AMechanicObject_Output::ToggleOutput(bool bNowActive)
{
}