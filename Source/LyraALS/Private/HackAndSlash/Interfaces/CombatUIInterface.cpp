// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Interfaces/CombatUIInterface.h"

// Add default functionality here for any ICombatUIInterface functions that are not pure virtual.
UPlayerUIComponent* ICombatUIInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UNPCUIComponent* ICombatUIInterface::GetNPC_UIComponent() const
{
	return nullptr;
}
