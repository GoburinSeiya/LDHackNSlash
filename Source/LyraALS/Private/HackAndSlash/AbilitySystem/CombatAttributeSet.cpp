// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/CombatAttributeSet.h"

UCombatAttributeSet::UCombatAttributeSet()
{
	//Health variables init
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);

	//rage variables init
	InitCurrentCinderCharge(1.f);
	InitMaxCinderCharge(1.f);

	//Combat variables init
	InitAttackPower(1.f);
	InitDefensePower(1.f);

	//Stance variables init
	InitCurrentStanceLevel(1.f);
	InitMaxStanceLevel(1.f);
	InitStanceDamage(1.f);
}
