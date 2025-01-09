// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Components/Combat/HeroCombatComponent.h"
#include "HackAndSlash/Items/Weapons/CombatHeroWeapon.h"

ACombatHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ACombatHeroWeapon>(GetCharacterWeaponByTag(InWeaponTag));
}
