// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "SpaceObjectComponent.h"
#include "TurretSubComponent.generated.h"


UENUM(BlueprintType)
enum class ETurretPartEnum : uint8
{
	TP_Base		UMETA(DisplayName = "Base"),
	TP_Swivel	UMETA(DisplayName = "Swivel"),
	TP_Gun		UMETA(DisplayName = "Gun")
};

/**
 * 
 */
UCLASS()
class PROJECTCENTAURI_API UTurretSubComponent : public USpaceObjectComponent
{
	GENERATED_BODY()
public:
	UTurretSubComponent();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Type")
		ETurretPartEnum PartType;

		const class UStaticMeshSocket *GetInSocket() const;
		const class UStaticMeshSocket *GetOutSocket() const;

	UFUNCTION(BlueprintCallable, Category = "Attachment")
		FName GetInSocketName(bool Safe = false) ;
	UFUNCTION(BlueprintCallable, Category = "Attachment")
		FName GetOutSocketName(bool Safe = false);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretStaticMesh(class UStaticMesh * NewMesh);

	bool IsValid();
	bool OutSocketExist();
	bool InSocketExist();

	bool AttachCompToOutSocket(UTurretSubComponent* ChildTurretComp);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMesh* Mesh;

	const class UStaticMeshSocket *GetInSocketSafe();
	const class UStaticMeshSocket *GetOutSocketSafe();


	UTurretSubComponent* GetAttachedComponent();

	void SetSockets();
private:
	const class UStaticMeshSocket* InSocket;
	const class UStaticMeshSocket* OutSocket;
	class UTurretSubComponent* AttachedActor;
	
};
