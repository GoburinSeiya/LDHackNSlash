// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Components/Combat/PawnCombatComponent.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
	ACombatWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	//we check if our map does not have the tag, if it returns null we need to add it, else it exists already in our map
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A Tag named %s has already been added as a carried weapon"), *InWeaponTagToRegister.ToString());
	//we validate the weapon to register
	check(InWeaponToRegister); 

	//if both check succeed we add to our map
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	//Now we check if we should equip the weapon automatically
	if(bRegisterAsEquippedWeapon)
	{
		 CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
	const FString WeaponString = FString::Printf(TEXT("A weapon named %s has been registered using the tag %s"), *InWeaponToRegister->GetName(),*InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
}
ACombatWeaponBase* UPawnCombatComponent::GetCharacterWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet)) //we check if this tag exists in our map
	{
		//If the weapon exists we want to store its reference in a local variable in memory
		if(ACombatWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			//we found a weapon so we return it, we must dereference the pointer to get hold of the pointer it points to
			return *FoundWeapon;
		}
	}
	//If both checks fail we do not have said weapon yet so we cant equip it, so we return null
	return nullptr;
}

ACombatWeaponBase* UPawnCombatComponent::GetCharacterCurrentlyEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid()) //If our currently equipped weapon isnt valid we return null outright
		return nullptr;

	return GetCharacterWeaponByTag(CurrentEquippedWeaponTag);
}
