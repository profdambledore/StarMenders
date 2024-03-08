// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "InGame_Master.generated.h"

UCLASS()
class STARMENDERS_API UInGame_Master : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

	// Called to update the visual elements

	// Called to set the owning player pointer
	void SetPlayerOwner(class ACharacter_Parent* NewOwner);

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
	/// -- Components - Global --
	// Widget switcher that allows the UI to swap between different states
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Global Components")
	UWidgetSwitcher* StateSwitcher = nullptr;

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

protected:
	// TMap of <int / FString> to change what the RecordingText shows
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Recording")
	TMap<int, FString> RecordingTextStates;

	// Pointer to the Character that owns this UserWidget
	class ACharacter_Parent* Player = nullptr;

private:

};
