// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Mechanics/MechanicObject_Button.h"

AMechanicObject_Button::AMechanicObject_Button()
{
	// Setup the components
	// Setup the button outer mesh
	ButtonOuterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Outer Mesh"));
	ButtonOuterMesh->SetupAttachment(Root, "");

	// Setup the button inner mesh
	ButtonInnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Inner Mesh"));
	ButtonInnerMesh->SetupAttachment(Root, "");

	// Setup the button trigger zone
	ButtonTriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Button Trigger Zone"));
	ButtonTriggerZone->SetupAttachment(Root, "");

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMechanicObject_Button::BeginPlay()
{
	Super::BeginPlay();

	// Add the overlap events to the ButtonTriggerZone
	// Add Overlap Events
	ButtonTriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AMechanicObject_Button::OnButtonBeginOverlap);
	ButtonTriggerZone->OnComponentEndOverlap.AddDynamic(this, &AMechanicObject_Button::OnButtonEndOverlap);

}

void AMechanicObject_Button::OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor has the tag "CanActivateButtons"
	if (OtherActor->ActorHasTag("CanActivateButtons")) {
		OverlapActors.Add(OtherActor);

		// If OverlapActors now has exactly one index, activate the button
		if (OverlapActors.Num() == 1 && ObjectState == On) {
			StartTrigger();
		}
	}
}

void AMechanicObject_Button::OnButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Check if the overlapping actor has the tag "CanActivateButtons"
	if (OtherActor->ActorHasTag("CanActivateButtons")) {
		OverlapActors.Remove(OtherActor);

		// If OverlapActors now is empty, deactivate the button
		if (OverlapActors.Num() == 0 && ObjectState != Off) {
			EndTrigger();
		}
	}
}


void AMechanicObject_Button::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMechanicObject_Button::StartTrigger()
{
	ObjectState = Active;

	// Activate all output objects
	for (AMechanicObject_Parent* i : OutputsObjects) {
		i->ActivateObject(true);
		i->BlueprintTestFunction();
	}
}

void AMechanicObject_Button::EndTrigger()
{
	ObjectState = On;

	// Deactivate all output devices
	for (AMechanicObject_Parent* i : OutputsObjects) {
		i->ActivateObject(false);
		i->BlueprintTestFunction();
	}
}

void AMechanicObject_Button::ActivateObject(bool bPositive)
{
	if (bPositive) {
		TriggerCount++;
	}
	else {
		TriggerCount--;
	}

	// Check if the TriggerCount has now reached the TriggerReqirements
	if (TriggerCount >= TriggerRequirement) {
		// Check if the object is currently being triggered.  If so, StartTrigger
		if (OverlapActors.Num() == 1) {
			StartTrigger();
		}
		ObjectState = EObjectState::On;
		UE_LOG(LogTemp, Warning, TEXT("State On in %s"), *this->GetName());
	}
	else {
		if (OverlapActors.Num() != 0) {
			EndTrigger();
		}

		ObjectState = EObjectState::Off;
	}
}