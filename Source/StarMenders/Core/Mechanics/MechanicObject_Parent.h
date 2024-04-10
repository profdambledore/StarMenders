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

public:	
	/// -- Global Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	/// -- Mechanic Properties - Details --
	// FString denoting the objects name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Properties")
	FName ObjectName;
};
