// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/CombatTypes/CombatStructTypes.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"


bool FCombatHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
