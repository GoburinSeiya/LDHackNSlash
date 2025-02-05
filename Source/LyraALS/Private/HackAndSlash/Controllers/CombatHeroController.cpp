// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Controllers/CombatHeroController.h"

ACombatHeroController::ACombatHeroController()
{
	FriendlyTeamId = FGenericTeamId(0);
}

FGenericTeamId ACombatHeroController::GetGenericTeamId() const
{
	return FriendlyTeamId;
}
