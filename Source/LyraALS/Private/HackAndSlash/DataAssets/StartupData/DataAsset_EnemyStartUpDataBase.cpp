// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/DataAssets/StartupData/DataAsset_EnemyStartUpDataBase.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpDataBase::GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if(!EnemyCombatAbilities.IsEmpty())
	{
		for( const TSubclassOf<UCombatEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities )
		{
			if(!AbilityClass) continue;

			//Construct spec
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
