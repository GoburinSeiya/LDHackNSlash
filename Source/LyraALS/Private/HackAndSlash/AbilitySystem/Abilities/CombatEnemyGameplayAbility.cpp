// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/Abilities/CombatEnemyGameplayAbility.h"
#include "HackAndSlash/Characters/CombatEnemyCharacter.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"

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

FGameplayEffectSpecHandle UCombatEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat, const FScalableFloat& InStanceDamageScalableFloat)
{
	check(EffectClass);

	//Step 1 construct context handle
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	//Step 2 Construct Effect spec handle
	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);
	
	//Step 3 Set set by caller magnitude
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		CombatGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		CombatGameplayTags::Shared_SetByCaller_StanceDamage,
		InStanceDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}
