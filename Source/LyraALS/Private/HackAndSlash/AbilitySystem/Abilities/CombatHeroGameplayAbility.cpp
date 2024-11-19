// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/Abilities/CombatHeroGameplayAbility.h"
#include "HackAndSlash/Characters/CombatHeroCharacter.h"
#include "HackAndSlash/Controllers/CombatHeroController.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"  
#include "HackAndSlash/Components/Combat/HeroCombatComponent.h"
#include "HackAndSlash/CombatGameplayTags.h"

ACombatHeroCharacter* UCombatHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if(!CachedHeroCharacter.IsValid()) //if our pointer is not valid, we want to store the cast result on it, smart ptr will cache it
	{
		CachedHeroCharacter = Cast<ACombatHeroCharacter>(CurrentActorInfo->AvatarActor); //this is why the function isnt cosnt
	}
	//We validate our CachedHeroCharacter, if it is valid we immediatly dereference it 
	return CachedHeroCharacter.IsValid()? CachedHeroCharacter.Get() : nullptr;
	//iow validate CachedHeroCharacter		If valid return				If not valid return
}

ACombatHeroController* UCombatHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!CachedHeroController.IsValid())
	{
		CachedHeroController = Cast<ACombatHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedHeroController.IsValid()? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UCombatHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UCombatHeroGameplayAbility::MakeHeroDamageSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
{
	check(EffectClass);

	//Construct Spec Handle
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	//Store inside our handle data our weapons base damage
	EffectSpecHandle.Data->SetSetByCallerMagnitude(CombatGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if(InCurrentAttackTypeTag.IsValid())
	{
		//Store inside our EffectSpecHandle Data The current combo count
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InCurrentComboCount);
	}
	
	return EffectSpecHandle;
}
