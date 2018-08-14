// Copyright 2018 Noe PERARD-GAYOT

#include "SpacePawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h" // Spring Arm
#include "Camera/CameraComponent.h" // Camera
#include "Components/ShipMovementComponent.h"
#include "Gameplay/SpacePlayerController.h"
#include "SpaceActor.h"
#include "ThrusterActor.h"

#if WITH_EDITOR
#include "Components/ArrowComponent.h"
#endif // WITH_EDITOR



//Axis Binding
const FName ASpacePawn::EngineThrustBinding("ThrustImpulse");
const FName ASpacePawn::MoveForwardBinding("MoveForward");
const FName ASpacePawn::MoveRightBinding("MoveRight");
const FName ASpacePawn::FireForwardBinding("FireForward");
const FName ASpacePawn::FireRightBinding("FireRight");

const FName  ASpacePawn::RotateYawBinding("Yaw Axis");
const FName  ASpacePawn::RotatePitchBinding("Pitch Axis");;
const FName  ASpacePawn::RotateRollBinding("Roll Axis");;

// Sets default values
ASpacePawn::ASpacePawn()
{
 	// Set this pawn NOT to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = false;

	PawnBaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spaceship"));
	RootComponent = PawnBaseMeshComponent;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1300.f;
	CameraBoom->RelativeRotation = FRotator(-70.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	MovementComponent = CreateDefaultSubobject<UShipMovementComponent>(TEXT("Movement Component"));
	//MovementComponent->SetAcceleration(Acceleration);


#if WITH_EDITOR
	auto Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->ArrowColor = FColor::Cyan;
	Arrow->EditorScale = 5;
	Arrow->SetupAttachment(RootComponent);
#endif // WITH_EDITOR

}

void ASpacePawn::OnConstruction(const FTransform & Transform)
{
	SetFreeCamera(true);
}

void ASpacePawn::AddForwardInput(float Val)
{
	if ((Controller != NULL) && (Val != 0.0f))
	{
		AddThrust(FVector(-1.f, 0.f, 0.f), Val);
	}
}

// Called when the game starts or when spawned
void ASpacePawn::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ASpacePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpacePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	
	//Controller Bindings
	PlayerInputComponent->BindAxis(RotateYawBinding, this, &ASpacePawn::AddYaw);
	PlayerInputComponent->BindAxis(RotatePitchBinding, this, &ASpacePawn::AddPitch);
	PlayerInputComponent->BindAxis(RotateRollBinding, this, &ASpacePawn::AddRoll);

	// set up gameplay key bindings
	//PlayerInputComponent->BindAction(EngineThrustBinding, EInputEvent::IE_Pressed, this, &ASpacePawn::AddForwardInput);


	PlayerInputComponent->BindAxis(MoveForwardBinding, this, &ASpacePawn::AddForwardInput);
	//PlayerInputComponent->BindAxis(MoveRightBinding);
	//PlayerInputComponent->BindAxis(FireForwardBinding);
	//PlayerInputComponent->BindAxis(FireRightBinding);

}

void ASpacePawn::SetFreeCamera(bool SetFree)
{
	if(SetFree)
	{
		CameraBoom->bUsePawnControlRotation = true;
	}
	else
	{
		CameraBoom->ResetRelativeTransform();
		CameraBoom->TargetArmLength = 1300.f;
		CameraBoom->RelativeRotation = FRotator(-70.f, 0.f, 0.f);
		CameraBoom->bUsePawnControlRotation = false;
	}
}


void ASpacePawn::AddThrust(FVector Direction, float Intensity )
{
	if(bCanMove)
	{
		// first ask those engine if they can participate :
		for (auto it : ChildActorList)
		{
			auto Thruster = Cast<AThrusterActor>(it);
			if (Thruster)
			{
				Thruster->DoThrust(FVector::DotProduct(Direction, Thruster->GetWorldDirection()) * Intensity , PawnBaseMeshComponent);
			}
		}

		//FVector InputVector = FVector(GetInputAxisValue(MoveForwardBinding), GetInputAxisValue(MoveRightBinding), 0 );
		//MovementComponent->ApplyMovement(InputVector);
	}
}

void ASpacePawn::AddYaw(float Value)
{
	if (bCanMove)
	{

	}
}

void ASpacePawn::AddPitch(float Value)
{
	if (bCanMove)
	{

	}
}

void ASpacePawn::AddRoll(float Value)
{
	if (bCanMove)
	{

	}
}

