// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"

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
