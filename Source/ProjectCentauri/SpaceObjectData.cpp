// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceObjectData.h"

bool FSpaceObjectData::IsValid() const
{
	if (Name.IsValid())
		return true;
	return false;
}