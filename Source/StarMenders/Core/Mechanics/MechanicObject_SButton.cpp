// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_SButton.h"

AMechanicObject_SButton::AMechanicObject_SButton()
{
	Tags.Add("IsInteractable");
}

void AMechanicObject_SButton::UseButton()
{
	ToggleInputActive();
}
