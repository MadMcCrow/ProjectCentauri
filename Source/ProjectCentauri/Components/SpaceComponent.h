// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceComponent.generated.h"



USTRUCT(BlueprintType)
struct FSpaceSocket
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		bool bIsUsed;

	UPROPERTY()
		FName SocketName;

	UPROPERTY()
		FString SocketTag;

public:

	FSpaceSocket(FName Name = FName(), FString Tag = FString(), bool Used = false)
	{
		SocketName = Name; SocketTag = Tag; bIsUsed = Used;
	}
};

UCLASS( ClassGroup=(SpaceActors), Blueprintable, meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API USpaceComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	/**
	 *	@brief AddComponent Function
	 *	
	 */
	UFUNCTION()
		virtual void AddComponent(TSubclassOf<USpaceComponent> ClassToAdd, FName SocketName );

protected:


private:

	UPROPERTY()
		TArray<FSpaceSocket> Sockets;

	UFUNCTION()
		virtual void SetSockets(class UMeshComponent * Setup);



};
