// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/DataAssets/StartupData/DataAsset_HeroStartUpData.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"



void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	//we loop through our array of abilities and grant them
	for(const FCombatHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if(!AbilitySet.IsValid()) continue; //if ability is invalid break to next loop and continue

		/** This settings are done so we can call our ability through the input tag, we require a source object, which is the entity using the ability, which is always the avatar actor, we must set the
		 level of the ability, and lastly we set up the dynamic tags which is what allows us to cast abilities on runtime **/
		
		//We construct our give ability spec
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant); //we set it using the ability to grant inside our ability set
		//We setup the source object
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		//Set level
		AbilitySpec.Level = ApplyLevel;
		// We get access to dynamic ability tags
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		//We give ability to out hero character
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
