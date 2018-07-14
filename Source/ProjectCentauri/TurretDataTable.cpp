// Copyright 2018 Noe PERARD-GAYOT

#include "TurretDataTable.h"
#include "ConstructorHelpers.h"
#include "TurretData.h"



UTurretDataTable::UTurretDataTable()
{

	RowStruct = FTurretData::StaticStruct();
	static ConstructorHelpers::FObjectFinder<UDataTable> TurretDataLookUpTable_BP (TEXT("DataTable'/Game/Blueprints/Data/TurretClasses.TurretClasses'"));
	GetFromOtherTable(TurretDataLookUpTable_BP.Object);
	SetupIndices();
}

void UTurretDataTable::GetFromOtherTable(UDataTable * Source)
{
	if (Source->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Display, TEXT("Found Correct Data"));
		CreateTableFromCSVString(Source->GetTableAsCSV());
	}else 
		UE_LOG(LogTemp, Error, TEXT("Invalid Data found"));
	
}

void UTurretDataTable::SetupIndices()
{
	FString ErrorContextString; // We'll use that in case of error
	TArray<FTurretData *> OutAllRows;
	GetAllRows(ErrorContextString, OutAllRows);
	TArray<FName> RowNames = GetRowNames();

	if (OutAllRows.Num() != RowNames.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Table Invalid"));
		return;
	}

	int CurrentIndex = 0;
	for (FTurretData* ShipDataRow : OutAllRows)
	{
		if (OutAllRows.IsValidIndex(CurrentIndex))
			Indices.Add(CurrentIndex, RowNames[CurrentIndex]);
	}

}
