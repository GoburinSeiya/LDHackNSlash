// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AnimInstances/CombatBaseAnimInstance.h"
#include "HackAndSlash/CombatFunctionLibrary.h"

bool UCombatBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UCombatFunctionLibrary::NativeActorDoesHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
