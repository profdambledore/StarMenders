// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Core/Data/LevelData.h"
#include "Core/Data/SelectorData.h"

#include "LevelSelect_Master.generated.h"

UCLASS()
class STARMENDERS_API ULevelSelect_Master : public UUserWidget
{
	GENERATED_BODY()
public:
	//virtual void NativeConstruct() override;

	//virtual void SynchronizeProperties() override;

	// Called to update the level currently being displayed by the widget.
	void UpdateWidgetData(FString NewName, FString NewTag);

public:
	/// -- Components
	// Text Box to display the planet's name
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UTextBlock* NameText = nullptr;

	// Text Box to display the planet's tagline
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Recording Components")
	UTextBlock* TaglineText = nullptr;

protected:

};
