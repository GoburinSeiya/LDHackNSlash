// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"
#include "HackAndSlash/Components/Combat/PawnCombatComponent.h"

void UCombatGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) //This function will be called right after an ability has been added to our ability system component
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if(AbilityActivationPolicy == ECombatAbilityActivationPolicy::OnGiven) //we check if our activation policy is done OnGiven
	{
		if(ActorInfo && !Spec.IsActive()) //Actor info is a struct containing many important things we want to access, check it with F12
		{						//Spec is the specification of our gameplay ability, contains things like its ability class, ability level  and current active status
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);		//To access this we must add our GameplayAbility component header file
		}
	}
}

void UCombatGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled); //this function is called when an ability has ended

	if(AbilityActivationPolicy == ECombatAbilityActivationPolicy::OnGiven) 
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);		//if our struct is valid, well clear our ability when it has ended deleting it from our component
		}
	}
}

UPawnCombatComponent* UCombatGameplayAbility::GetPawCombatComponentFromActorInfo() const
{
	//Iterates through the components the actor hass and returns the class that matches with the result
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UCombatAbilitySystemComponent* UCombatGameplayAbility::GetGameplayAbilityComponentFromActorInfo() const
{
	return Cast<UCombatAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}


