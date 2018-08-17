// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceComponent.generated.h"


/**
*	@brief FSpaceSocket Structure
*	Holds the information about the sockets
*/
USTRUCT(BlueprintType)
struct FSpaceSocket
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		FName SocketName;

	UPROPERTY()
		FString SocketTag;

	UPROPERTY()
		FTransform SocketTransform;

protected:

	UPROPERTY()
		bool bIsUsed;

public:
	// Constructor
	FSpaceSocket(FName Name = FName(), FString Tag = FString(), FTransform Transform = FTransform(), bool Used = false)
	{
		SocketName = Name; SocketTag = Tag; bIsUsed = Used; SocketTransform = Transform;
	}

	inline bool HasTag(FString Tag) { return (SocketTag == Tag); }

	friend bool operator==(const FSpaceSocket& LHS, const FSpaceSocket& RHS) { return (LHS.SocketName == RHS.SocketName && LHS.SocketTag == RHS.SocketTag); }


	inline void Use(bool Used) { bIsUsed = Used; }

};


UCLASS( ClassGroup=(SpaceActors), Abstract)
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
	 *	@param ClassToAdd the class of component added
	 *	@param SocketName The FName of the Socket
	 */
	UFUNCTION()
		virtual void AddComponent(TSubclassOf<USpaceComponent> ClassToAdd, FName SocketName );

	/**
	*	@brief AddComponent Function
	*	@param ClassToAdd the class of component added
	*	@param SocketName The FName of the Socket
	*/
	UFUNCTION(BlueprintCallable, Category = "Centauri|Components", meta = (DisplayName = "Add Component"))
		void AddComponent_BP(TSubclassOf<USpaceComponent> ClassToAdd, FName SocketName) { AddComponent(ClassToAdd, SocketName); }


public:


	/**
	*	@brief GetMeshComponent
	*	@return UMeshComponent : a pointer to the mesh used for this component
	*/
	UFUNCTION()
		virtual UMeshComponent * GetMeshComponent() const { return  Mesh; }

private:

	/**
	*	@brief Mesh property
	*	A pointer to a Mesh, either skeletal or static.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Centauri|Mesh", meta = (AllowPrivateAccess = true))
		class UMeshComponent * Mesh;

	/**
	*	@brief CreateComponent Function
	*	@return true if it managed to spawn an actor
	*/
	UFUNCTION()
		virtual	USpaceComponent * CreateComponent(TSubclassOf<USpaceComponent> ClassToAdd);

private:
	/**
	*	@brief Sockets property
	*	Stores the information to the Sockets used in this component
	*/
	UPROPERTY()
		TArray<FSpaceSocket> Sockets;

protected:

	/**
	*	@brief SetSockets 
	*	@param Setup : the mesh you want to get sockets added to this class 
	*/
	UFUNCTION()
		virtual void SetSockets(class UMeshComponent * Setup);

public:

	/**
	*	@brief GetSocketsByTag
	*	Get the socket array (Copy)
	*	@see Sockets
	*/
	UFUNCTION()
		FORCEINLINE TArray<FSpaceSocket> GetSockets() const { return Sockets; }

	/**
	*	@brief GetSocketsByTag
	*	Get the socket array (Copy)
	*	@note For Blueprints
	*/
	UFUNCTION(BlueprintPure, Category = "Centauri|Components", meta = (DisplayName ="Get Socket list"))
		FORCEINLINE TArray<FSpaceSocket> GetSockets_BP() const { return Sockets; }

	/**
	*	@brief GetSocketsByTag
	*	@param Tag: the tag to find in Sockets
	*	@param Out: the sockets with specified tags
	*/
	UFUNCTION()
		void GetSocketsByTag(const FString &Tag, TArray<FSpaceSocket> &Out) const;


	/**
	*	@brief GetSocketsByTag_BP
	*	@param Tag :the tag to find in Sockets
	*	@return the sockets with specified tags
	*	@note For Blueprints
	*/
	UFUNCTION(BlueprintPure, Category = "Centauri|Components", meta = (DisplayName = "Get Sockets by tag"))
		FORCEINLINE TArray<FSpaceSocket> GetSocketsByTag_BP(const FString &Tag)  const { TArray<FSpaceSocket> Out; GetSocketsByTag(Tag, Out); return Out; }


	/**
	 *	@brief GetSpaceSocketTransform
	 *	@param Socket : a struct describing the socket you want
	 *	@return the transform of the socket
	 */
	UFUNCTION()
		virtual FTransform GetSpaceSocketTransform(const FSpaceSocket &Socket);

	/**
	*	@brief GetSpaceSocketTransform
	*	@param Tag : A string we should search for
	*	@param Out: An array of Transforms to store the results. Will be emptied
	*	@return true if a socket was found
	*/
	UFUNCTION()
		virtual bool GetSpaceSocketTransformByTag(const FString & Tag, TArray<FTransform> & Out);


	// UsceneComponent Override
	virtual FTransform GetSocketTransform(FName SocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;

};
