// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AnimInstances/Hero/CombatHeroLinkedAnimInstance.h"
#include "HackAndSlash/AnimInstances/Hero/CombatHeroAnimInstance.h"

UCombatHeroAnimInstance* UCombatHeroLinkedAnimInstance::GetCombatHeroAnimInstance() const
{
	return Cast<UCombatHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
