// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/Abilities/CombatEnemyGameplayAbility.h"
#include "HackAndSlash/Characters/CombatEnemyCharacter.h"
#include "HackAndSlash/Characters/CombatEnemyCharacter.h"

ACombatEnemyCharacter* UCombatEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if(!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<ACombatEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid()? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UCombatEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
