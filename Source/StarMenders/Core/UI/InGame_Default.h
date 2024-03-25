// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "InGame_Default.generated.h"

UCLASS()
class STARMENDERS_API UInGame_Default : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	void SetupState();

protected:
	/// -- Recording Functions --
	// Button Binds
	// Binds for Hovering and Release of the Play Button
	UFUNCTION()
	void OnPlayButtonHovered();

	UFUNCTION()
	void OnPlayButtonReleased();

	// Binds for Hovering and Release of the Record Button
	UFUNCTION()
	void OnRecordButtonHovered();

	UFUNCTION()
	void OnRecordButtonReleased();

	// Binds for Hovering and Release of the Delete Button
	UFUNCTION()
	void OnDeleteButtonHovered();

	UFUNCTION()
	void OnDeleteButtonReleased();

	// Bind for UnHovered on all buttons
	UFUNCTION()
	void OnAllButtonUnhovered();

	// Called to change the text in the RecordingText TextBlock
	void UpdateRecordingText(int State);

public:
	/// -- Components - Recording --
	// Button used to play the current recordings of all pads
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UButton* PlayButton = nullptr;

	// Image used to display the play icon on the Play button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UImage* PlayImage = nullptr;

	// Button used to record on the current pad
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UButton* RecordButton = nullptr;

	// Image used to display the play icon on the Record button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UImage* RecordImage = nullptr;

	// Button used to delete the recording on the current pad
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UButton* DeleteButton = nullptr;

	// Image used to display the play icon on the Delete button
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UImage* DeleteImage = nullptr;

	// Text Box to display some informative text when a button is hovered
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UTextBlock* RecordingText = nullptr;

	/// -- Pointers--
	// Pointer to the master UI that this state is contained in
	class UInGame_Master* MasterUI = nullptr;

	class ACharacter_Default* DefaultCharacter = nullptr;

protected:
	// TMap of <int / FString> to change what the RecordingText shows
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recording")
	TMap<int, FString> RecordingTextStates;
};
