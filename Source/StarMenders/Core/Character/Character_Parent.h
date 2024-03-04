// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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
	void MoveX(float AxisValue);

	// Called to move the character on the Y axis
	void MoveY(float AxisValue);

	// Called to make the camera jump
	void StartJump();

	// Called to make the character interact
	void Interact();

	// Called to make the character's camera rotate
	void RotateCamera(FVector2D AxisValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/// -- Components
	// CameraComponent of the character's first person view
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* FirstPersonCamera = nullptr;

	// SpringArmComponent of the character's pick up item location
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* PickUpSpringArm = nullptr;

	// PhysicsHandleComponent used to pick up objects in the world
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPhysicsHandleComponent* ObjectPhysicsHandle = nullptr;


private:
	/// -- Actives --
	// Bool denoting if the character can move or not
	bool bMovementDisabled = false;

	/// -- Component Data --
	// Float denoting the character's pick up spring arm
	float PickUpArmLength = 300.0f;

	// Actor pointer storing the actor currently being held by this character
	// May not be needed
	//AActor* ActorHeld = nullptr;
};
