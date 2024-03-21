// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"

#include "Character_Parent.generated.h"

UCLASS()
class STARMENDERS_API ACharacter_Parent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Parent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// -- Inputs --
	// Called to move the character on the X axis
	virtual void MoveX(float AxisValue);

	// Called to move the character on the Y axis
	virtual void MoveY(float AxisValue);

	// Called to make the camera jump
	void StartJump();

	// Called to make the character interact
	virtual void Interact();

	// Called to make the character's camera rotate
	void RotateCamera(FVector2D AxisValue);

	// Called to make the character enter their menu
	void ToggleMenu(bool bInMenu);

	// Called to make the character interact with their UI element
	void UIInteract(bool bInMenu);

	/// -- Interaction --
	// Called to return CurrentRecordPad
	class ARecordPad* GetCurrentRecordPad();

	// Called to set the CurrentRecordPad
	void SetCurrentRecordPad(class ARecordPad* NewRecordPad);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components
	// CameraComponent of the character's first person view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* FirstPersonCamera = nullptr;

	// PhysicsHandleComponent used to pick up objects in the world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPhysicsHandleComponent* ObjectPhysicsHandle = nullptr;

	// WidgetComponent used to display the InGame UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* MenuWidgetComponent;

	// WidgetInteractionComponent used to interact with MenuWidgetComponent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetInteractionComponent* WidgetInteractionComponent;


protected:
	/// -- Actives --
	// Bool denoting if the character can move or not
	bool bMovementDisabled = false;

	// Pointer to the record pad currently being accessed
	class ARecordPad* CurrentRecordPad = nullptr;

	/// -- Component Data --
	// Float denoting the character's pick up spring arm
	float PickUpArmLength = 300.0f;
	
	/// -- UI --
	// Pointer to the UI added to the viewport
	class UInGame_Master* MenuUI = nullptr;

	/// -- Recording and Playback
	// Float denoting the tick rate of the recording and playback timer
	float TimerTickRate = 0.1f;


};
