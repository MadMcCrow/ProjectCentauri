// Copyright 2018 Noe PERARD-GAYOT

#include "ShipPawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h" // Spring Arm
#include "Camera/CameraComponent.h" // Camera
#include "Components/ShipMovementComponent.h"
#include "SpaceActor.h"


//Axis Binding
const FName AShipPawn::EngineThrustBinding("EngineThrust");
const FName AShipPawn::MoveForwardBinding("MoveForward");
const FName AShipPawn::MoveRightBinding("MoveRight");
const FName AShipPawn::FireForwardBinding("FireForward");
const FName AShipPawn::FireRightBinding("FireRight");

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	ShipComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Spaceship"));
	RootComponent = ShipComponent;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 3000.f;
	CameraBoom->RelativeRotation = FRotator(-70.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	MovementComponent = CreateDefaultSubobject<UShipMovementComponent>(TEXT("Movement Component"));
	//MovementComponent->SetAcceleration(Acceleration);
	

}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ApplyMovement();
#if !UE_BUILD_SHIPPING
	UE_LOG(LogActor, Display, TEXT("Ship pawn ticking"));
#endif

}

// Called to bind functionality to input
void AShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(EngineThrustBinding);
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);

}


void AShipPawn::ApplyMovement()
{
	if(bCanMove)
	{
		FVector InputVector = FVector(GetInputAxisValue(MoveForwardBinding), GetInputAxisValue(MoveRightBinding), 0 );
		//MovementComponent->ApplyMovement(InputVector);
	}
}

void AShipPawn::UpdateChildActors()
{
	// for now we do nothing, just so we're in the clear
}

