// Copyright 2018 Noe PERARD-GAYOT

#include "CameraPawn.h"
#include "Camera/CameraComponent.h" // Camera
#include "GameFramework/SpringArmComponent.h" // Spring Arm

#include "CentauriController.h"

const FName ACameraPawn::RotateYawBinding("Rotate Camera (Yaw)");
const FName ACameraPawn::RotatePitchBinding("Rotate Camera (Pitch)");
const FName ACameraPawn::RotateRollBinding("Rotate Camera (Roll)");
const FName ACameraPawn::ForwardBinding("Move Camera (Forward)");
const FName ACameraPawn::RightBinding("Move Camera (Right)");

const FName ACameraPawn::DollyBinding("Camera Zoom");

// Sets default values
ACameraPawn::ACameraPawn()
{
	// Setting default values:
	BorderRotationSpeed = 20;
	BorderSize = 0.25;


 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	PlayerCameraBoom= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	PlayerCameraBoom->SetupAttachment(RootComponent);
	PlayerCameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	PlayerCameraBoom->TargetArmLength = 0.f;
	PlayerCameraBoom->RelativeRotation = FRotator(-70.f, 0.f, 0.f);
	PlayerCameraBoom->bDoCollisionTest = true; // Don't want to see the inside of objects
	PlayerCameraBoom->bUsePawnControlRotation = true;


	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = PlayerCameraBoom;
	PlayerCamera->SetupAttachment(PlayerCameraBoom);
	PlayerCamera->bUsePawnControlRotation = false;	// Camera does rotate based on controller
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	//SetActorTickEnabled(false);

}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldRotateOnBorder)
		RotateOnBorder(DeltaTime);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

ACentauriController * ACameraPawn::GetCentauriController()
{
	return Cast<ACentauriController>(GetController());
}

void ACameraPawn::RotateOnBorder(float DeltaTime)
{
	FVector2D Dir = GetCentauriController()->GetBorderDirection(BorderSize);
	FRotator Angle(Dir.Y, Dir.X, 0.f);
	Angle *= DeltaTime * BorderRotationSpeed;
	PlayerCamera->AddLocalRotation(Angle);
}

void ACameraPawn::SetLookAtObject(AActor * Target, float Margin)
{
	if (!Target)
		return;
	FBox TargetBox = Target->CalculateComponentsBoundingBoxInLocalSpace(true);
	PlayerCameraBoom->TargetArmLength = TargetBox.GetExtent().GetMax() * 2;
	PlayerCameraBoom->AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

