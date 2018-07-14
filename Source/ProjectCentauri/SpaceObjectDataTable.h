// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpaceObjectData.h"
#include "SpaceObjectDataTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCENTAURI_API USpaceObjectDataTable : public UDataTable
{
	GENERATED_BODY()
public:
	USpaceObjectDataTable();


protected:
	TMap<int16, FName > Indices;

	template <typename DataType>
	FORCEINLINE DataType GetRowByIndex_Backend(int index)
	{
		FName * RowNamePtr = nullptr;
		RowNamePtr = Indices.Find(index);
		if (RowNamePtr)
		{
			FString ErrorContextString; // We'll use that in case of error
			return *(FindRow<DataType>(*RowNamePtr, ErrorContextString));
		}
		return DataType();
	}


	template <typename DataType>
	FORCEINLINE DataType GetRowByName_Backend(FName Name)
	{
		FName * RowNamePtr = &Name; // this way the pointer is forced to be valid
		FString ErrorContextString; // We'll use that in case of error
		return *(FindRow<DataType>(*RowNamePtr, ErrorContextString));
	};


	template <typename DataType, typename DataTableType>
	FORCEINLINE static DataType GetRowStruct_Backend(int index)
	{
		DataType FStruct;
		DataTableType* SampleList = NewObject<DataTableType>();
		FStruct = SampleList->GetRowByIndex(index);
		// sanity check
#if !UE_BUILD_SHIPPING
		if (!FStruct.IsValid())
			UE_LOG(LogTemp, Error, TEXT("Data Incorrect"));
#endif
		// get rid of the reference so it gets GC
		SampleList = nullptr;
		return FStruct;
	}

	template <typename DataType, typename DataTableType>
	FORCEINLINE static DataType GetRowStruct_Backend(FName Name)
	{
		DataType FStruct;
		DataTableType* SampleList = NewObject<DataTableType>();
		FStruct = SampleList->GetRowByName(Name);
		// sanity check
#if !UE_BUILD_SHIPPING
		if (!FStruct.IsValid())
			UE_LOG(LogTemp, Error, TEXT("Data Incorrect"));
#endif
		// get rid of the reference so it gets GC
		SampleList = nullptr;
		return FStruct;
	}



private:
	
	virtual void GetFromOtherTable(UDataTable* Source);
	virtual void SetupIndices();



};

