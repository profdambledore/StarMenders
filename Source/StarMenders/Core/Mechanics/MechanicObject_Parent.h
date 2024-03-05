// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MechanicObject_Parent.generated.h"

UCLASS()
class STARMENDERS_API AMechanicObject_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMechanicObject_Parent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// -- Trigger Function --
	// Called when this object recieves it's input
	virtual void StartTrigger();

	// Called when this object stops recieving it's input
	virtual void EndTrigger();

	// Called to modify the visual elements of this object
	UFUNCTION(BlueprintImplementableEvent)
	void ModifyVisualElements(bool bSetOn);

	// Blueprint Test Function -- ONLY USE FOR TESTING
	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintTestFunction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Global Components --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root = nullptr;

	/// -- Mechanic Properties --
	// FString denoting the objects name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Properties")
	FString ObjectName;

	// Boolean denoting if the mechanic is active or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mechanic Properties")
	bool bActive = false;

	/// -- Outputs --
	// TArray of pointers to other MechanicObjects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outupts")
	TArray<AMechanicObject_Parent*> OutputsObjects; 

};
