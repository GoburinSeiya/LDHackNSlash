// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AnimInstances/CombatCharacterAnimInstance.h"
#include "HackAndSlash/Characters/CombatBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCombatCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter= Cast<ACombatBaseCharacter>(TryGetPawnOwner());

	if(OwningCharacter) //check if character is valid
	{
		UCharacterMovementComponent* MovementComponent = OwningCharacter->GetCharacterMovement(); 
	}
}

void UCombatCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter  || !OwningCharacter->GetCharacterMovement())
	{
		return;
	}
}
