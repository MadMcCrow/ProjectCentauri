// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class PROJECTCENTAURI_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

	UFUNCTION(BlueprintCallable, Category = "Projectile | Aiming")
		void SetTarget(class USceneComponent* TargetComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile | Setup")
		class UStaticMesh* ProjectileMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile | Setup")
		float MaxSpeed = 300.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile | Setup")
		bool bIsHoming = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile | Setup")
		float LifeSpan = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile | Setup")
		float CollisionRadius = 3.0f;


	UFUNCTION(BlueprintCallable, Category = "Projectile | Collision")
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:	
	
	class UProjectileMovementComponent* ProjectileMovement;
	class UStaticMeshComponent*			ProjectileComponent;
	class USphereComponent*				CollisionSphere;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
