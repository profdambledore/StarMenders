// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Parent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACharacter_Parent::ACharacter_Parent()
{
	// Setup the character's components
	// Setup the Player's Cameras
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(90.0f, 0.0f, 0.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetupAttachment(GetMesh(), "");

	// Setup the object physics handle
	ObjectPhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Object Physics Handle"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacter_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacter_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacter_Parent::MoveX(float AxisValue)
{
	if (AxisValue != 0 && !bMovementDisabled) {
		// Move on the X axis based on the input's axis value
		AddMovementInput(FirstPersonCamera->GetForwardVector(), AxisValue, false);
		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Parent::MoveY(float AxisValue)
{
	if (AxisValue != 0 && !bMovementDisabled) {
		// Move on the X axis based on the input's axis value
		AddMovementInput(FirstPersonCamera->GetRightVector(), AxisValue, false);
		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Parent::StartJump()
{
	Jump();
}

void ACharacter_Parent::Interact()
{
	// Check if this character is currently holding an object
	if (ObjectPhysicsHandle->GetGrabbedComponent()) {
		// If so, stop grabbing the component
		ObjectPhysicsHandle->ReleaseComponent();
	}
	else {
		// Fire a line trace infront of this character
		FHitResult TraceHit;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);

		bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, GetActorLocation(), GetActorLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), ECC_WorldDynamic, TraceParams);
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), FColor::White, true, 5, 0, 5);
		// Check if the object hit has a tag of "CanBePickedUp"
		if (TraceHit.GetActor()) {
			if (TraceHit.GetActor()->ActorHasTag(FName("CanBePickedUp"))) {
				UE_LOG(LogTemp, Warning, TEXT("Object hit = %s"), *TraceHit.GetActor()->GetName());
				// If so, grab the actor via the ObjectPhysicsHandle
				// Calculate the object's component bounds to grab it in the center of the object
				FVector BoxExtents;
				BoxExtents = TraceHit.GetComponent()->GetLocalBounds().BoxExtent;
				BoxExtents = BoxExtents / 6;
				ObjectPhysicsHandle->GrabComponentAtLocationWithRotation(TraceHit.GetComponent(), "", TraceHit.GetComponent()->GetComponentLocation() + BoxExtents, TraceHit.GetComponent()->GetComponentRotation());
			}
		}
	}
}

void ACharacter_Parent::RotateCamera(FVector2D AxisValue)
{
	if (!bMovementDisabled) {
		// Rotate on the X axis based on the input's axis value
		AddControllerYawInput(AxisValue.X);
		AddControllerPitchInput(AxisValue.Y);

		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(GetActorLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

