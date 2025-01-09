// Fill out your copyright notice in the Description page of Project Settings.  


#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"  
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"  

  
void UCombatAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)  
{  
	if (!InInputTag.IsValid())  
	{ 
		return;  
	}  

	//if valid, we loop through all of our activatable abilities  

	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())  
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;  
		TryActivateAbility(AbilitySpec.Handle);  
	}
}  


void UCombatAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)  
{  

}  

  

void UCombatAbilitySystemComponent::GrantHeroWeaponAbilities(  
const TArray<FCombatHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)  
{  
	if(InDefaultWeaponAbilities.IsEmpty())  
		return;  

  

	for(const FCombatHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)  
	{
		if(!AbilitySet.IsValid()) continue;  

		
		//Call function of gameplay ability system to give ability
		//As per usual build the ability spec before //To define our spec we need to include our CombatGameplayAbility.h
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);  
		AbilitySpec.SourceObject = GetAvatarActor();  
		AbilitySpec.Level = ApplyLevel;  
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);  
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));  

	}
}

void UCombatAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if(InSpecHandlesToRemove.IsEmpty())
		return;

	for(const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if(SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}  
