// Copyright 2018 Noe PERARD-GAYOT

#include "ShipDataTable.h"
#include "ConstructorHelpers.h"
#include "ShipData.h"



UShipDataTable::UShipDataTable()
{

	RowStruct = FShipData::StaticStruct();
	static ConstructorHelpers::FObjectFinder<UDataTable> SpaceShipLookUpTable_BP(TEXT("DataTable'/Game/Blueprints/Data/ShipClasses.ShipClasses'"));
	GetFromOtherTable(SpaceShipLookUpTable_BP.Object);
	SetupIndices();
}

void UShipDataTable::GetFromOtherTable(UDataTable * Source)
{
	if (Source->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Display, TEXT("Found Correct Data"));
		CreateTableFromCSVString(Source->GetTableAsCSV());
	}else 
		UE_LOG(LogTemp, Error, TEXT("Invalid Data found"));
	
}

void UShipDataTable::SetupIndices()
{
	FString ErrorContextString; // We'll use that in case of error
	TArray<FShipData*> OutAllRows;
	GetAllRows(ErrorContextString, OutAllRows);
	TArray<FName> RowNames = GetRowNames();

	if (OutAllRows.Num() != RowNames.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Table Invalid"));
		return;
	}

	int CurrentIndex = 0;
	for (FShipData* ShipDataRow : OutAllRows)
	{
		if (OutAllRows.IsValidIndex(CurrentIndex))
			Indices.Add(CurrentIndex, RowNames[CurrentIndex]);
	}

}
