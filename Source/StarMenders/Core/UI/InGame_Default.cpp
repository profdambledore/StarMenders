// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UI/InGame_Default.h"

#include "Core/UI/InGame_Master.h"
#include "Core/Character/Character_Parent.h"
#include "Core/Mechanics/RecordPad.h"

void UInGame_Default::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup Button Binds for the Play Button
	PlayButton->OnHovered.AddDynamic(this, &UInGame_Default::OnPlayButtonHovered);
	PlayButton->OnReleased.AddDynamic(this, &UInGame_Default::OnPlayButtonReleased);

	// Setup Button Binds for the Record Button
	RecordButton->OnHovered.AddDynamic(this, &UInGame_Default::OnRecordButtonHovered);
	RecordButton->OnReleased.AddDynamic(this, &UInGame_Default::OnRecordButtonReleased);

	// Setup Button Binds for the Delete Button
	DeleteButton->OnHovered.AddDynamic(this, &UInGame_Default::OnDeleteButtonHovered);
	DeleteButton->OnReleased.AddDynamic(this, &UInGame_Default::OnDeleteButtonReleased);

	// Setup Button binds for All buttons
	PlayButton->OnUnhovered.AddDynamic(this, &UInGame_Default::OnAllButtonUnhovered);
	RecordButton->OnUnhovered.AddDynamic(this, &UInGame_Default::OnAllButtonUnhovered);
	DeleteButton->OnUnhovered.AddDynamic(this, &UInGame_Default::OnAllButtonUnhovered);
}

void UInGame_Default::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UInGame_Default::OnPlayButtonHovered()
{
	if (MasterUI->GetPlayerOwner()->GetCurrentRecordPad()) {
		if (MasterUI->GetPlayerOwner()->GetCurrentRecordPad()->GetHasRecording()) {
			UpdateRecordingText(1);
		}
		else {
			UpdateRecordingText(2);
		}
	}
	else {
		UpdateRecordingText(2);
	}

}

void UInGame_Default::OnPlayButtonReleased()
{
	
}

void UInGame_Default::OnRecordButtonHovered()
{
	UpdateRecordingText(3);
}

void UInGame_Default::OnRecordButtonReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Pressed"));

	// Call StartRecord on the assocciated pad
	if (MasterUI->GetPlayerOwner()->GetCurrentRecordPad()) {
		MasterUI->GetPlayerOwner()->GetCurrentRecordPad()->StartRecording(MasterUI->GetPlayerOwner()->GetController());
	}
}

void UInGame_Default::OnDeleteButtonHovered()
{
	if (MasterUI->GetPlayerOwner()->GetCurrentRecordPad()) {
		if (MasterUI->GetPlayerOwner()->GetCurrentRecordPad()->GetHasRecording()) {
			UpdateRecordingText(4);
		}
		else {
			UpdateRecordingText(5);
		}
	}
	else {
		UpdateRecordingText(5);
	}
}

void UInGame_Default::OnDeleteButtonReleased()
{
}

void UInGame_Default::OnAllButtonUnhovered()
{
	UpdateRecordingText(0);
}

void UInGame_Default::UpdateRecordingText(int State)
{
	// Check if the state argument exists in the TMap.
	if (RecordingTextStates.Find(State)) {
		FString out = RecordingTextStates.FindRef(State);
		RecordingText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *out)));
	}
	else {
		FString out = RecordingTextStates.FindRef(-1);
		RecordingText->SetText(FText::FromString(FString::Printf(TEXT("%s"), *out)));
	}
}