// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Components/Combat/PawnCombatComponent.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"
#include "Components/BoxComponent.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
	ACombatWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	//we check if our map does not have the tag, if it returns null we need to add it, else it exists already in our map
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A Tag named %s has already been added as a carried weapon"), *InWeaponTagToRegister.ToString());
	//we validate the weapon to register
	check(InWeaponToRegister);

	//if both check succeed we add to our map
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	//We access the delegates we've created
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
	
	//Now we check if we should equip the weapon automatically
	if(bRegisterAsEquippedWeapon)
	{
		 CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
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

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	ACombatWeaponBase* WeaponToToggle = GetCharacterCurrentlyEquippedWeapon();

	check(WeaponToToggle);

	if(bShouldEnable)
	{
		//Dont forget to add header file of box component
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly); //we only need overlap events so call query only
	}
	else
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
	}

	//TODO: Handle collision boxes
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}
