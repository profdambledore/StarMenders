// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/Character_Parent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

#include "Core/Mechanics/Mechanic_WorldObject.h"

#include "Core/UI/InGame_Master.h"

// Sets default values
ACharacter_Parent::ACharacter_Parent()
{
	// Setup the character's components
	// Setup the Player's Cameras
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetupAttachment(GetMesh(), "");

	// Setup the object physics handle
	ObjectPhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Object Physics Handle"));

	// Setup the MenuWidgetComponent and the WidgetInteractionComponent
	MenuWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget Component"));
	MenuWidgetComponent->SetupAttachment(GetMesh(), "");
	MenuWidgetComponent->SetGenerateOverlapEvents(false);

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Interaction Component"));
	WidgetInteractionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;
	WidgetInteractionComponent->SetupAttachment(FirstPersonCamera, "");

	// Setup the character's gameplay tags
	Tags.Add("CanActivateButtons"); // Allows the character to activate buttons

	// Get the InGame UserWidget for the character and store it
	static ConstructorHelpers::FClassFinder<UUserWidget>UIClass(TEXT("/Game/Core/UI/WBP_InGame"));
	if (UIClass.Succeeded()) {
		MenuWidgetComponent->SetWidgetClass(UIClass.Class);
	};

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacter_Parent::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to the interact widget class
	MenuUI = Cast<UInGame_Master>(MenuWidgetComponent->GetWidget());
	MenuUI->SetPlayerOwner(this);	
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
		// Get the camera's forward vector X and Y, removing the Z
		FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
		Direction = FVector(Direction.X, Direction.Y, 0.0f).GetSafeNormal();
		AddMovementInput(Direction, AxisValue, false);
		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
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
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
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

		bool InteractTrace = GetWorld()->LineTraceSingleByChannel(TraceHit, FirstPersonCamera->GetComponentLocation(), FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), ECC_WorldDynamic, TraceParams);
		DrawDebugLine(GetWorld(), FirstPersonCamera->GetComponentLocation(), FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), FColor::White, true, 5, 0, 5);
		// Check if the object hit has a tag of "CanBePickedUp"
		if (TraceHit.GetActor()) {
			if (TraceHit.GetActor()->ActorHasTag(FName("CanBePickedUp"))) {
				// Next, check if the object is currently being grabbed.
				// Cast to the WorldObject, call GetCurrentGrabber and release the object from the grabber if not nullptr
				AMechanic_WorldObject* CG = Cast<AMechanic_WorldObject>(TraceHit.GetActor());
				if (CG->GetCurrentGrabber()) {
					CG->GetCurrentGrabber()->ObjectPhysicsHandle->ReleaseComponent();
				}
				// If so, grab the actor via the ObjectPhysicsHandle
				// Calculate the object's component bounds to grab it in the center of the object
				FVector BoxExtents;
				BoxExtents = TraceHit.GetComponent()->GetLocalBounds().BoxExtent;
				BoxExtents = BoxExtents / 6;
				ObjectPhysicsHandle->GrabComponentAtLocationWithRotation(TraceHit.GetComponent(), "", TraceHit.GetComponent()->GetComponentLocation() + BoxExtents, TraceHit.GetComponent()->GetComponentRotation());

				// Finally, update the WorldObject's CurrentGrabber with this character
				CG->SetCurrentGrabber(this);
			}
		}
	}
}

void ACharacter_Parent::RotateCamera(FVector2D AxisValue)
{
	if (!bMovementDisabled) {
		//UE_LOG(LogTemp, Warning, TEXT("Rotate = %f / %f"), AxisValue.X, AxisValue.Y);

		// Rotate on the X axis based on the input's axis value
		AddControllerYawInput(AxisValue.X);
		AddControllerPitchInput(AxisValue.Y);

		if (ObjectPhysicsHandle->GetGrabbedComponent()) {
			// Update the PhysicsHandles TargetLocation
			ObjectPhysicsHandle->SetTargetLocationAndRotation(FirstPersonCamera->GetComponentLocation() + (UKismetMathLibrary::GetForwardVector(FirstPersonCamera->GetComponentRotation()) * PickUpArmLength), UKismetMathLibrary::FindLookAtRotation(ObjectPhysicsHandle->GetGrabbedComponent()->GetComponentLocation(), FirstPersonCamera->GetComponentLocation()));
		}
	}
}

void ACharacter_Parent::ToggleMenu(bool bInMenu)
{
	MenuWidgetComponent->SetVisibility(bInMenu);
	bMovementDisabled = bInMenu;
}

void ACharacter_Parent::UIInteract(bool bInMenu)
{
	if (bInMenu) {
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	}
}