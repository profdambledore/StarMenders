// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Mechanics/MechanicObject_Parent.h"
#include "MechanicObject_Output.generated.h"

UCLASS()
class STARMENDERS_API AMechanicObject_Output : public AMechanicObject_Parent
{
	GENERATED_BODY()

public:
	/// -- Mechanic Functions - Inputs --
	// Called by the LevelController to set the output to always active if nessasary
	void SetAlwaysActive();

	// Called by Input Objects to increase the current input count
	void IncreaseInputAmount(bool bPositive);

	// Called when InputCount >= InputRequirement
	virtual void ToggleOutput(bool bNowActive);

public:
	/// -- Mechanic Properties - Output --
	// Integar denoting the amount of inputs required to turn this object's output on
	// For example, if the output object was a door, it would require this amount of inputs to open the door
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output Properties")
	int InputRequirement = 0;

	// Integar denoting the current amount of inputs currently infuencing this object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Output Properties")
	int InputCount;

	// Boolean denoting if this output is always active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output Properties")
	bool bOutputAlwaysActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object")
	TSubclassOf<AActor> ObjectToSpawn;
};
