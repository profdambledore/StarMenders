// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Default.h"

ARecordPad* ACharacter_Default::GetCurrentRecordPad()
{
	return CurrentRecordPad;
}

void ACharacter_Default::SetCurrentRecordPad(ARecordPad* NewRecordPad)
{
	CurrentRecordPad = NewRecordPad;
}