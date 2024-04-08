// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MechanicObject_Parent.generated.h"

UENUM(BlueprintType, Category = "Mechanics")
enum EObjectState
{
	Off UMETA(DisplayName = "Off"),
	On UMETA(DisplayName = "On"),
	Active UMETA(DisplayName = "Active")
};

UCLASS()
class STARMENDERS_API AMechanicObject_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMechanicObject_Parent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Active Functions --
	// Called when external objects activate this object
	virtual void ActivateObject(bool bPositive);

	// Called to modify the visual elements of this object
	UFUNCTION(BlueprintImplementableEvent)
	void ModifyVisualElements(bool bSetOn);

	// Blueprint Test Function -- ONLY USE FOR TESTING
	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintTestFunction();

	// Called to reset this object to it's default state
	virtual void ResetToDefault();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Trigger Function --
	// Called when this object recieves it's input
	virtual void StartTrigger();

	// Called when this object stops recieving it's input
	virtual void EndTrigger();

public:	
	/// -- Global Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	/// -- Mechanic Properties - Details --
	// FString denoting the objects name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Properties")
	FName ObjectName;

	/// -- Mechanic Properties - Actives --
	// Boolean denoting if the mechanic is active or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Properties")
	bool bActive = false;

	// Enum denoting the object's current state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Properties")
	TEnumAsByte<EObjectState> ObjectState;

	/// -- Inputs --
	// Integar denoting the amount of triggers required to turn this object on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	int TriggerRequirement;

	// Integar denoting the current amount of triggers currently infuencing this object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	int TriggerCount;

	/// -- Outputs --
	// TArray of pointers to other MechanicObjects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outupts")
	TArray<AMechanicObject_Parent*> OutputsObjects; 

};
