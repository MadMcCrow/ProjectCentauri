// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SpaceObjectComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API USpaceObjectComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceObjectComponent();
protected:

	bool SetupSocketList();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Name")
		FName Name = FName("Default");

	virtual void Setup();
	virtual void SetRealMass(float RealMass);
	float Mass = 100.f;

	TArray < class UStaticMeshSocket * > GetSocketsList() const;
	TArray < class UStaticMeshSocket * > GetSocketsByTag(FString TagDiscriminent);

private:

	TArray < class UStaticMeshSocket * > SocketsList;
	bool bSocketsListIsSet = false;

	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
