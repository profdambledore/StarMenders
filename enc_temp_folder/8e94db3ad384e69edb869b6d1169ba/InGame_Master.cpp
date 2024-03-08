// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UI/InGame_Master.h"

#include "Core/Character/Character_Parent.h"
#include "Core/Mechanics/RecordPad.h"

void UInGame_Master::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup Button Binds for the Play Button
	PlayButton->OnHovered.AddDynamic(this, &UInGame_Master::OnPlayButtonHovered);
	PlayButton->OnReleased.AddDynamic(this, &UInGame_Master::OnPlayButtonReleased);

	// Setup Button Binds for the Record Button
	RecordButton->OnHovered.AddDynamic(this, &UInGame_Master::OnRecordButtonHovered);
	RecordButton->OnReleased.AddDynamic(this, &UInGame_Master::OnRecordButtonReleased);

	// Setup Button Binds for the Delete Button
	DeleteButton->OnHovered.AddDynamic(this, &UInGame_Master::OnDeleteButtonHovered);
	DeleteButton->OnReleased.AddDynamic(this, &UInGame_Master::OnDeleteButtonReleased);

	// Setup Button binds for All buttons
	PlayButton->OnUnhovered.AddDynamic(this, &UInGame_Master::OnAllButtonUnhovered);
	RecordButton->OnUnhovered.AddDynamic(this, &UInGame_Master::OnAllButtonUnhovered);
	DeleteButton->OnUnhovered.AddDynamic(this, &UInGame_Master::OnAllButtonUnhovered);
}

void UInGame_Master::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UInGame_Master::SetPlayerOwner(ACharacter_Parent* NewOwner)
{
	Player = NewOwner;
}

void UInGame_Master::OnPlayButtonHovered()
{
	if (Player->GetCurrentRecordPad()) {
		if (Player->GetCurrentRecordPad()->GetHasRecording())
		UpdateRecordingText(1);
	}
	else {
		UpdateRecordingText(2);
	}

}

void UInGame_Master::OnPlayButtonReleased()
{
}

void UInGame_Master::OnRecordButtonHovered()
{
	UpdateRecordingText(3);
}

void UInGame_Master::OnRecordButtonReleased()
{
}

void UInGame_Master::OnDeleteButtonHovered()
{
	if (Player->GetCurrentRecordPad()) {
		if (Player->GetCurrentRecordPad()->GetHasRecording())
			UpdateRecordingText(4);
	}
	else {
		UpdateRecordingText(5);
	}
}

void UInGame_Master::OnDeleteButtonReleased()
{
}

void UInGame_Master::OnAllButtonUnhovered()
{
	UpdateRecordingText(0);
}

void UInGame_Master::UpdateRecordingText(int State)
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
