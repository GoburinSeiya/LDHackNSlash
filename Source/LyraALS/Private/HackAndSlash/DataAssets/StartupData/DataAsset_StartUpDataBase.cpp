// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/DataAssets/StartupData/DataAsset_StartUpDataBase.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	check(InASCToGive); //validating variable

	//Call the function to grant on given abilities
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	//Call the function to grant abilities on reaction
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UCombatGameplayAbility>>& InAbilitiesToGive,
	UCombatAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) //validate
	{
		return;
	}

	for(const TSubclassOf<UCombatGameplayAbility>& Ability : InAbilitiesToGive) //iterate on our abilities array, we use a constant reference for each variable in the array, like this we iterate over every element without creating a copy
	{
		if(!Ability) continue; //if ability is not valid we continue to the next element

		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability); //We create our spec
		//Construct our spec
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); //we must setup our source object, we use the avatar actor
		AbilitySpec.Level = ApplyLevel; //We define our function
		
		InASCToGive->GiveAbility(AbilitySpec); //we call our give ability function in our Ability combat system component, func takes a spec as input so we need to create one beforehand
	}
}
