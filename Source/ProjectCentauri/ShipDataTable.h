// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "SpaceObjectDataTable.h"
#include "ShipData.h"
#include "ShipDataTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCENTAURI_API UShipDataTable : public USpaceObjectDataTable
{
	GENERATED_BODY()
public:
	UShipDataTable();

	FORCEINLINE struct FShipData GetRowByIndex(int Index)		{ return GetRowByIndex_Backend<FShipData>(Index);}
	FORCEINLINE static struct FShipData GetRowStruct(int Index) { return GetRowStruct_Backend<FShipData, UShipDataTable>(Index); }
private:
	//TMap<int16, FName > Indices;
	virtual void GetFromOtherTable(UDataTable* Source) override;
	virtual void SetupIndices() override;

};
