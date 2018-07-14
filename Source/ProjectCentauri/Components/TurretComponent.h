// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "TurretSubComponent.h"
#include "TurretData.h"
#include "TurretComponent.generated.h"

/**
 * UTurretComponent :
 *  @brief This is the turret component class. it is the Whole Turret and a sub component at the same time,
 *  as this is also the base.
 */
UCLASS()
class PROJECTCENTAURI_API UTurretComponent : public UTurretSubComponent
{
	GENERATED_BODY()
public:
	UTurretComponent();

	void UseTurretData(FName TurretName);
	void UseTurretData(int index);

	FORCEINLINE void UseTurretData(FTurretData NewStats) { TurretStatistics = NewStats; };

	UFUNCTION(BlueprintCallable, Category = "Rotation")
	void SetTargetRotation(FRotator SolidAngle);
	UFUNCTION(BlueprintCallable, Category = "Rotation")
	FRotator GetGunRotation() const;
	UFUNCTION(BlueprintCallable, Category = "Data")
	FTurretData GetTurretData() const;
	UFUNCTION(BlueprintCallable, Category = "Setup")
		float GetSwivelOffset() const;
	UFUNCTION(BlueprintCallable, Category = "Rotation")
		bool IsAligned() const;
	UFUNCTION(BlueprintCallable, Category = "Fire")
		FTransform GetMuzzleTransform() const;


protected:
	FTurretData TurretStatistics;

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	class UTurretSubComponent * Swivel;
	class UTurretSubComponent * Gun;
	float RotAccuracy = 0.1;
	FRotator TargetAlign;
	FRotator CurrentAlign;
	void RotateTurret();
	void ApplyTurretData();
	bool bIsAligned = false;
};
