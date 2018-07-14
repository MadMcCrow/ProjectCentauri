// Copyright 2018 Noe PERARD-GAYOT

#include "TurretData.h"

bool FTurretData::IsValid() const
{
	if (BaseMesh && GunMesh && SwivelMesh)
		return true;
	return false;
}