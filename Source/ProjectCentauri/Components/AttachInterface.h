// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttachInterface.generated.h"


/**
*	@brief FSpaceSocket Structure
*	Holds the information about the sockets
*/
USTRUCT(BlueprintType)
struct FSpaceSocket
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName SocketName;

	UPROPERTY()
		FString SocketTag;

	UPROPERTY()
		FTransform SocketTransform;

protected:

	UPROPERTY()
		bool bIsUsed;

	UPROPERTY()
		bool bTransformIsSet;

public:
	// Constructor
	FSpaceSocket(FName Name = FName(), FString Tag = FString(), FTransform Transform = FTransform(), bool Used = false)
	{
		SocketName = Name;
		SocketTag = Tag;
		bIsUsed = Used;
		if (!FTransform::Identity.Equals(Transform, 0.000001f))
		{
			SocketTransform = Transform;
			bTransformIsSet = true;
		}
		else {
			bTransformIsSet = false;
		}
	}

	inline bool HasTag(FString Tag) { return (SocketTag == Tag); }

	friend bool operator==(const FSpaceSocket& LHS, const FSpaceSocket& RHS) 
	{
		return (LHS.SocketName == RHS.SocketName && LHS.SocketTag == RHS.SocketTag && !LHS.SocketTransform.Equals(RHS.SocketTransform, 0.0001f));
	}


	inline void Use(bool Used) { bIsUsed = Used; }

};


// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UAttachInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	@class IAttachInterface
 *	This interface adds the attachment functionnality to any component.
 */
class PROJECTCENTAURI_API IAttachInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	*	@brief CreateComponent Function
	*	@return pointer to the component if it managed to spawn it
	*/
	UFUNCTION()
		virtual	class UMeshComponent * GetMesh() const = 0;

	/**
	*	@brief AddComponent Function
	*	@param ClassToAdd the class of component added
	*	@param SocketName The FName of the Socket
	*	@return true if Actor was created
	*/
	UFUNCTION()
		virtual bool AddComponent(TSubclassOf<class USceneComponent> ClassToAdd, FName SocketName);



protected:

	/**
	*	@brief SetSockets
	*	@param Setup : the mesh you want to get sockets added to this class
	*/
	UFUNCTION()
		virtual void SetSockets(class UMeshComponent * Setup);

private:
	
	/**
	 *	@brief CreateComponent Function
	 *	@return pointer to the component if it managed to spawn it
	 */
	UFUNCTION()
		virtual	USceneComponent * CreateComponent(TSubclassOf<class USceneComponent> ClassToAdd);

public:

	/**
	 *	@brief GetSocketsByTag
	 *	Get the socket array (Copy)
	 *	@see Sockets
	 */
	UFUNCTION()
		virtual TArray<FSpaceSocket> GetSockets() const = 0;

	/**
	 *	@brief GetSocketsByTag
	 *	Get the socket array (Copy)
	 *	@note For Blueprints
	 */
	UFUNCTION(BlueprintCallable, Category = "Centauri|Components", meta = (DisplayName = "Get Socket list"))
		virtual	TArray<FSpaceSocket> GetSockets_BP() const { return GetSockets(); }

	/**
	 *	@brief GetSocketsByTag
	 *	@param Tag: the tag to find in Sockets
	 *	@param Out: the sockets with specified tags
	 */
	UFUNCTION()
		virtual void GetSocketsByTag(const FString &Tag, TArray<FSpaceSocket> &Out) const;


	/**
	 *	@brief GetSocketsByTag_BP
	 *	@param Tag :the tag to find in Sockets
	 *	@return the sockets with specified tags
	 *	@note For Blueprints
	 */
	UFUNCTION(BlueprintCallable, Category = "Centauri|Components", meta = (DisplayName = "Get Sockets by tag"))
		virtual TArray<FSpaceSocket> GetSocketsByTag_BP(const FString &Tag)  const { TArray<FSpaceSocket> Out; GetSocketsByTag(Tag, Out); return Out; }


	/**
	 *	@brief GetSpaceSocketTransform
	 *	@param Socket : a struct describing the socket you want
	 *	@return the transform of the socket
	 */
	UFUNCTION()
		virtual FTransform GetSpaceSocketTransform(const FSpaceSocket &Socket) const;

	/**
	 *	@brief GetSpaceSocketTransform
	 *	@param Tag : A string we should search for
	 *	@param Out: An array of Transforms to store the results. Will be emptied
	 *	@return true if a socket was found
	 */
	UFUNCTION()
		virtual bool GetSpaceSocketTransformByTag(const FString & Tag, TArray<FTransform> & Out);

	/**
	 *	@brief GetSpaceSocketTransform
	 *	@param Tag : A string we should search for
	 *	@param Out: An array of Transforms to store the results. Will be emptied
	 *	@return true if a socket was found
	 */
	UFUNCTION(BlueprintCallable, Category = "Centauri|Components", meta = (DisplayName = "Get Sockets transform by tag"))
		virtual  TArray<FTransform> GetSpaceSocketTransformByTag_BP(const FString & Tag) { TArray<FTransform> Out; GetSpaceSocketTransformByTag(Tag, Out); return Out; }

protected:

	UFUNCTION()
		virtual FTransform GetSocketFromScreenSpace(FVector2D &SceenCoordinates) const;
};
