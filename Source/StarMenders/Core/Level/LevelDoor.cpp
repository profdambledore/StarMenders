// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Level/LevelDoor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/MovementComponent.h"

#include "Core/Character/Character_Parent.h"

// Sets default values
ALevelDoor::ALevelDoor()
{
	// Setup Components
	// Root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame Mesh"));
	Frame->SetupAttachment(Root, "");

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	Plane->SetupAttachment(Root, "");

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetupAttachment(Root, "");

	CaptureSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Capture Spring Arm"));
	CaptureSpringArm->SetupAttachment(Root, "");

	CaptureCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture Camera"));
	CaptureCamera->SetupAttachment(Root, "");

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelDoor::BeginPlay()
{
	Super::BeginPlay();

	// Add Overlap Events
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ALevelDoor::OnTZBeginOverlap);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ALevelDoor::OnTZEndOverlap);

	UpdateClipPlane();
	
}

void ALevelDoor::OnTZBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACharacter_Parent::StaticClass())) {
		//UE_LOG(LogTemp, Warning, TEXT("Adding"));
		TriggerZoneOverlaps.Add(OtherActor);
	}
}

void ALevelDoor::OnTZEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACharacter_Parent::StaticClass())) {
		TriggerZoneOverlaps.Remove(OtherActor);
	}
}

// Called every frame
void ALevelDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// First, check if the door is open
	if (bDoorOpen && PairedDoor) {
		//https://www.youtube.com/watch?v=6BT-Ux56KBs&list=PLlYisyZ--cm_wsMGpy2C9Ewwm--jsv5Cm&index=1 
		// Caluclate the distance 
		FTransform TF = GetActorTransform();
		TF.SetScale3D(FVector(TF.GetScale3D().X * -1, TF.GetScale3D().Y * -1, TF.GetScale3D().Z));
		FVector ITL = TF.InverseTransformPosition(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetSocketLocation(""));
		FVector FL = PairedDoor->GetTransform().TransformPosition(ITL);
		PairedDoor->CaptureCamera->SetWorldLocation(FL);


		// Finally, update the paired door's capture camera
		PairedDoor->CaptureCamera->SetWorldRotation(GetInverseRotation(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation()));
		
		if (!TriggerZoneOverlaps.IsEmpty()) {
			GetShouldTeleport();
		}
	};

}
void ALevelDoor::SetDoorState(bool bSetToClosed)
{
	bDoorOpen = bSetToClosed;
}

void ALevelDoor::UpdateClipPlane()
{
	if (PairedDoor) {
		CaptureCamera->bEnableClipPlane = true;
		CaptureCamera->ClipPlaneBase = Plane->GetComponentLocation() + (Root->GetForwardVector() * -3);
		CaptureCamera->ClipPlaneNormal = Root->GetForwardVector();
	}
}

void ALevelDoor::GetShouldTeleport()
{
	// Check if the object colliding with the trigger zone is a Character
	if (!TriggerZoneOverlaps.IsEmpty()) {
		if (TriggerZoneOverlaps[0]) {
			if (TriggerZoneOverlaps[0]->IsA(ACharacter_Parent::StaticClass())) {
				// Next, check if the character is overlapping the portal
				if (GetIsCrossingPortal(TriggerZoneOverlaps[0]->GetActorLocation(), GetActorLocation(), Root->GetForwardVector())) {
					UE_LOG(LogTemp, Warning, TEXT("GST"));
					TeleportCharacter(TriggerZoneOverlaps[0]);
				};
			}
		}
	}
}

bool ALevelDoor::GetIsCrossingPortal(FVector PointToCheck, FVector PortalLocation, FVector PortalNormal)
{
	// Check if the distance of the portal's normal is greater than or equal too the distance between the point to check and the portal's location
	bool bIsInFront = FVector::DotProduct(PortalNormal, PointToCheck - PortalLocation) >= 0.0f;

	// Next, make a plane from the portal location and the normal (the direction of the portal)
	// And use the plane to calculate if the point is intersecting the portal
	FPlane PortalPlane = UKismetMathLibrary::MakePlaneFromPointAndNormal(PortalLocation, PortalNormal);
	float T; FVector IntersectionLocation;
	bool bIsIntersecting = UKismetMathLibrary::LinePlaneIntersection(LastPosition, PointToCheck, PortalPlane, T, IntersectionLocation);

	// Calculate if we are crossing the portal, update bLastInFront and store the PointToCheck for the next check
	bool bIsCrossingPlane = bIsIntersecting && !bIsInFront && bLastInFront;
	bLastInFront = bIsInFront; LastPosition = PointToCheck;

	return bIsCrossingPlane;
}

void ALevelDoor::TeleportCharacter(AActor* CharacterToTeleport)
{
	ACharacter_Parent* Char = Cast<ACharacter_Parent>(CharacterToTeleport);
	FTransform TF = GetActorTransform();
	TF.SetScale3D(FVector(TF.GetScale3D().X * -1, TF.GetScale3D().Y * -1, TF.GetScale3D().Z));
	FVector ITL = TF.InverseTransformPosition(CharacterToTeleport->GetActorLocation());
	FVector FL = PairedDoor->GetTransform().TransformPosition(ITL);

	CharacterToTeleport->SetActorLocation(FL);
	CharacterToTeleport->SetActorRotation(GetInverseRotation(CharacterToTeleport->GetActorRotation()));
	Char->GetController()->SetControlRotation(GetInverseRotation(Char->GetController()->GetControlRotation()));

	// Now update Char's velocity
	FVector Vel = Char->GetMovementComponent()->Velocity; Vel.Normalize(0.0001);
	FVector CIT = UKismetMathLibrary::InverseTransformDirection(GetActorTransform(), Vel);
	FVector OutVel = UKismetMathLibrary::TransformDirection(PairedDoor->GetActorTransform(), CIT.MirrorByVector(FVector(1.0f, 0.0f, 0.0f)).MirrorByVector(FVector(0.0f, 1.0f, 0.0f)));
	Char->GetMovementComponent()->Velocity = OutVel * Char->GetMovementComponent()->Velocity.Length();
}

FRotator ALevelDoor::GetInverseRotation(FRotator InRotator)
{
	// First, setup some holding values for each axis
	FVector OutX, OutY, OutZ;

	// Then break the rotation of the input into axes, returning a vector for pitch, roll and yaw based on the rotation's position on each axis 
	UKismetMathLibrary::BreakRotIntoAxes(InRotator, OutX, OutY, OutZ);

	// Then make a rotator from the axes vectors after mirroring each axis on the inverse tranform of the paired door
	// This will flip the camera from being positive or negative (aka it will point in the opposite direction of the player on the paired door)
	FRotator OR = UKismetMathLibrary::MakeRotationFromAxes(
		PairedDoor->GetTransform().TransformVector(GetTransform().InverseTransformVector(OutX).MirrorByVector(FVector(1.0f, 0.0f, 0.0f)).MirrorByVector(FVector(0.0f, 1.0f, 0.0f))),
		PairedDoor->GetTransform().TransformVector(GetTransform().InverseTransformVector(OutY).MirrorByVector(FVector(1.0f, 0.0f, 0.0f)).MirrorByVector(FVector(0.0f, 1.0f, 0.0f))),
		PairedDoor->GetTransform().TransformVector(GetTransform().InverseTransformVector(OutZ).MirrorByVector(FVector(1.0f, 0.0f, 0.0f)).MirrorByVector(FVector(0.0f, 1.0f, 0.0f)))
	);

	return OR;
}
