// Fill out your copyright notice in the Description page of Project Settings.  


#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"  
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatHeroGameplayAbility.h"
#include "HackAndSlash/CombatGameplayTags.h"

  
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
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(CombatGameplayTags::InputTag_MustBeHeld))
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
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

bool UCombatAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());
	
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	
	//We get the ability to activate by tag				Convert the ability tag to a container with func	Array of ability specs
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if(!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	return false;
}  
