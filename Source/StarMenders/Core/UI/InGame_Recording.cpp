// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UI/InGame_Recording.h"

#include "Core/UI/InGame_Master.h"
#include "Core/Character/Character_Record.h"

void UInGame_Recording::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup Button Binds for the Play Button
	EndButton->OnHovered.AddDynamic(this, &UInGame_Recording::OnEndButtonHovered);
	EndButton->OnReleased.AddDynamic(this, &UInGame_Recording::OnEndButtonReleased);

	// Setup Button binds for All buttons
	EndButton->OnUnhovered.AddDynamic(this, &UInGame_Recording::OnEndButtonUnhovered);
}

void UInGame_Recording::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UInGame_Recording::OnEndButtonHovered()
{
	InfoText->SetText(FText::FromString(FString::Printf(TEXT("Stop recording early and save what you have recorded"))));
}

void UInGame_Recording::OnEndButtonReleased()
{
	// Cast to the recording character and end the recording early
	Cast<ACharacter_Record>(MasterUI->GetPlayerOwner())->EndRecording();
}

void UInGame_Recording::OnEndButtonUnhovered()
{
	InfoText->SetText(FText::FromString(FString::Printf(TEXT(""))));
}

void UInGame_Recording::UpdateRemainingTime(float InTimeRemaining)
{
	int a = InTimeRemaining;
	a += 1;
	RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%i"), a)));
}
