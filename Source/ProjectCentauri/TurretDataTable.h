// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "SpaceObjectDataTable.h"
#include "TurretData.h"
#include "TurretDataTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCENTAURI_API UTurretDataTable : public USpaceObjectDataTable
{
	GENERATED_BODY()
public:
	UTurretDataTable();

	FORCEINLINE struct FTurretData GetRowByIndex(int Index) {	return GetRowByIndex_Backend<FTurretData>(Index);}
	FORCEINLINE struct FTurretData GetRowByName(FName Name) {	return GetRowByName_Backend<FTurretData>(Name); }

	FORCEINLINE static struct FTurretData GetRowStruct(int Index)  { return GetRowStruct_Backend<FTurretData, UTurretDataTable>(Index); }
	FORCEINLINE static struct FTurretData GetRowStruct(FName Name) { return GetRowStruct_Backend<FTurretData, UTurretDataTable>(Name); }

private:
	//TMap<int16, FName > Indices;
	virtual void GetFromOtherTable(UDataTable* Source) override;
	virtual void SetupIndices() override;

};
