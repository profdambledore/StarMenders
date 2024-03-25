// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "InGame_Recording.generated.h"

UCLASS()
class STARMENDERS_API UInGame_Recording : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	// Called to update the remaining time text
	void UpdateRemainingTime(float InTimeRemaining);

protected:
	/// -- Recording Functions --
	// Button Binds
	// Binds for Hovering, UnHovered and Release of the End Recording Button
	UFUNCTION()
	void OnEndButtonHovered();

	UFUNCTION()
	void OnEndButtonReleased();

	UFUNCTION()
	void OnEndButtonUnhovered();

public:
	/// -- Components - Recording --
	// Button used to play the current recordings of all pads
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UButton* EndButton = nullptr;

	// Image used to display the play icon on the Play button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UImage* EndImage = nullptr;

	// Text Box to display some informative text when a button is hovered
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UTextBlock* InfoText = nullptr;

	// Text Box to display how long the player has left in their recording
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UTextBlock* RemainingTimeText = nullptr;

	/// -- Pointers--
	// Pointer to the master UI that this state is contained in
	class UInGame_Master* MasterUI = nullptr;
	
};
