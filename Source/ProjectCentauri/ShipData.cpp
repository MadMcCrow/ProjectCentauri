// Copyright 2018 Noe PERARD-GAYOT

#include "ShipData.h"

bool FShipData::IsValid() const
{
	if (Mesh && Skin)
		return true;
	return false;
}