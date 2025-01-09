// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AnimInstances/Hero/CombatHeroAnimInstance.h"
#include "HackAndSlash/Characters/CombatHeroCharacter.h"

void UCombatHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation(); //Here we do call super cause we are modifying our own version of this function in parent

	if(OwningHeroCharacter)
	{
		Cast<ACombatHeroCharacter>(OwningHeroCharacter);
	}
}
