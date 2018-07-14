// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceObjectDataTable.h"
#include "ConstructorHelpers.h"




USpaceObjectDataTable::USpaceObjectDataTable()
{
	RowStruct = FSpaceObjectData::StaticStruct();
}

void USpaceObjectDataTable::GetFromOtherTable(UDataTable * Source)
{
	if (Source->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Display, TEXT("Found Correct Data"));
		CreateTableFromCSVString(Source->GetTableAsCSV());
	}else 
		UE_LOG(LogTemp, Error, TEXT("Invalid Data found"));
	
}

void USpaceObjectDataTable::SetupIndices()
{
	FString ErrorContextString; // We'll use that in case of error
	TArray<FSpaceObjectData*> OutAllRows;
	GetAllRows(ErrorContextString, OutAllRows);
	TArray<FName> RowNames = GetRowNames();

	if (OutAllRows.Num() != RowNames.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Table Invalid"));
		return;
	}

	int CurrentIndex = 0;
	for (FSpaceObjectData* DataRow : OutAllRows)
	{
		if (OutAllRows.IsValidIndex(CurrentIndex))
			Indices.Add(CurrentIndex, RowNames[CurrentIndex]);
	}

}

/*
template <typename DataType>
DataType USpaceObjectDataTable::GetRowByIndexBackend(int index)
{
#if !UE_BUILD_SHIPPING
	// this chunk of code isn't necessary if you're not putting the wrong type of data inside
	if (DataType::StaticClass() != TSubclassOf<FSpaceObjectData>::StaticClass())
		UE_LOG(LogTemp, Error, TEXT("About to crash in a very hard way"));
#endif
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
DataType USpaceObjectDataTable::GetRowByNameBackend(FName Name)
{
#if !UE_BUILD_SHIPPING
	// this chunk of code isn't necessary if you're not putting the wrong type of data inside
	if (DataType::StaticClass() != TSubclassOf<FSpaceObjectData>::StaticClass())
		UE_LOG(LogTemp, Error, TEXT("About to crash in a very hard way"));
#endif
	FName * RowNamePtr = &Name; // this way the pointer is forced to be valid
	FString ErrorContextString; // We'll use that in case of error
	return *(FindRow<DataType>(*RowNamePtr, ErrorContextString));
};
*/


