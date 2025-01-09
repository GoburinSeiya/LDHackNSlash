// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatBaseCharacter.h"
	#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h" //include our ability system component
#include "HackAndSlash/AbilitySystem/CombatAttributeSet.h" //Include our attribute set

// Sets default values
ACombatBaseCharacter::ACombatBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//Disable ticking if not needed, if you ever find you do, reenable
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false; //make our decals affect the ground only, not our character mesh

	CombatAbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>(TEXT("CombatAbilitySystemComponent"));

	CombatAttributeSet = CreateDefaultSubobject<UCombatAttributeSet>(TEXT("CombatAttributeSet"));
}

UAbilitySystemComponent* ACombatBaseCharacter::GetAbilitySystemComponent() const
{
	return GetCombatAbilitySystemComponent();
}

void ACombatBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(CombatAbilitySystemComponent)
	{
		CombatAbilitySystemComponent->InitAbilityActorInfo(this, this);

		//ensure(!CharacterStartUpDataBase.IsNull()); /** If this returns false then this macro will trigger a breakpoint in debug mode, outputing messages to the editor log **/
		ensureMsgf(!CharacterStartUpDataBase.IsNull(), TEXT("Forgot to assign startup data to %s"), *GetName()); //we print a error message with the name of the character
	}
}



