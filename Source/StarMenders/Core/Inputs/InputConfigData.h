// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "InputAction.h"

#include "InputConfigData.generated.h"

UCLASS()
class STARMENDERS_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/// -- Movement Inputs --
	// Pointer to the forward/backwards player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* MoveXInput = nullptr;

	// Pointer to the strafe player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* MoveYInput = nullptr;

	// Pointer to the mouse player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* CameraInput = nullptr;

	// Pointer to the toggle menu player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* MenuInput = nullptr;

	// Pointer to the jump player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* JumpInput = nullptr;

	// Pointer to the interact player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* InteractInput = nullptr;
};
