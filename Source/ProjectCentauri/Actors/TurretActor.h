// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "TurretData.h"
#include "GameFramework/Actor.h"
#include "TeamInterface.h"
#include "TurretActor.generated.h"

UCLASS()
class PROJECTCENTAURI_API ATurretActor : public AActor , public ITeamInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretActor();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	struct FTurretData TurretStatistics;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret", meta = (ExposeOnSpawn = "true"))
	int TurretDataIndex = 0;


	UFUNCTION(BlueprintCallable, Category = "Fire")
		bool CanFire();

private:
	class UTurretComponent* TurretComp;
	class UAimingComponent* AimingComp;

	float FireCooldown = 0;


	// Team Interface
private:
	FTeam TurretTeam;
protected:
	FORCEINLINE virtual void SetTeam(const FTeam &NewTeam) override { TurretTeam = NewTeam; }
	FORCEINLINE virtual FTeam & GetTeam()  override { return TurretTeam; }



};
