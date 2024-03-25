// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Character/Character_Parent.h"
#include "Character_Default.generated.h"

UCLASS()
class STARMENDERS_API ACharacter_Default : public ACharacter_Parent
{
	GENERATED_BODY()
	
public:
	/// -- Interaction --
	// Called to return CurrentRecordPad
	class ARecordPad* GetCurrentRecordPad();

	// Called to set the CurrentRecordPad
	void SetCurrentRecordPad(class ARecordPad* NewRecordPad);

protected:
	// Pointer to the record pad currently being accessed
	class ARecordPad* CurrentRecordPad = nullptr;
};
