// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "SpaceObjectComponent.h"
#include "ShipData.h"
#include "ShipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API UShipComponent : public USpaceObjectComponent
{
	GENERATED_BODY()

public:	
	UShipComponent();  //Constructor
	~UShipComponent(); //Destructor

protected:
	virtual void BeginPlay() override;

	
	FShipData ShipData;
	int ShipDataIndex = 0;
	bool bIsNameValid;


	UFUNCTION(BlueprintCallable, Category = "Setup") //should be removed when everything works fine
	virtual void Setup() override;

	UFUNCTION(BlueprintCallable, Category = "Setup") //should be removed when everything works fine
		void GetDataFromTable();


	TArray<class UThrusterTrailComponent*> Trails;

public:	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//setters and getters
	FShipData GetShipData();
	void  SetShipData(FShipData Data);

private:
	class UThrusterTrailComponent* AddParticleTrail(class UStaticMeshSocket* AttachSocket);
	class UThrusterTrailComponent* AddParticleTrailRuntime(class UStaticMeshSocket* AttachSocket); //Do not use : Crash
};
