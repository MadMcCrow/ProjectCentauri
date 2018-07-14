// Copyright 2018 Noe PERARD-GAYOT

#include "TeamInterface.h"

FTeam ITeamInterface::GetTeam_BP()
{
	return GetTeam();
}

void ITeamInterface::SetTeam_BP(const FTeam & NewTeam)
{
	SetTeam(NewTeam);
}
