// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/WidgetSwitcher.h"

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

	// Called to update the active state
	void UpdateActiveState(FString InState);

	// Called to get the owning player pointer
	class ACharacter_Parent* GetPlayerOwner();

protected:

public:
	/// -- Components - Global --
	// Widget switcher that allows the UI to swap between different states
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Global Components")
	UWidgetSwitcher* StateSwitcher = nullptr;

	// State
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Global Components")
	class UInGame_Default* DefaultState = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Global Components")
	class UInGame_Recording* RecordState = nullptr;

protected:
	// Pointer to the Character that owns this UserWidget
	class ACharacter_Parent* Player = nullptr;

private:

};
