// Copyright 2018 Noe PERARD-GAYOT

#include "ProjectileActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	CollisionSphere->SetupAttachment(RootComponent);
	RootComponent = CollisionSphere;

	ProjectileComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	ProjectileComponent->SetupAttachment(RootComponent);
	ProjectileComponent->SetStaticMesh(ProjectileMesh);

	CollisionSphere->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionSphere->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);		// set up a notification for when this component hits something
	
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileComponent;

	ProjectileMovement->InitialSpeed = MaxSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->bIsHomingProjectile = bIsHoming;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = LifeSpan;
}

void AProjectileActor::SetTarget(USceneComponent* TargetComponent)
{
	if (bIsHoming)
	{
		ProjectileMovement->HomingTargetComponent = TargetComponent;
	}
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileActor::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{

}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

