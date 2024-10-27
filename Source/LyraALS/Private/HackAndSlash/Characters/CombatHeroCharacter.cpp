// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatHeroCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "HackAndSlash/DataAssets/Input/DataAsset_InputConfig.h"
#include "HackAndSlash/Components/Input/CombatInputComponent.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h" //include our ability system component
#include "HackAndSlash/DataAssets/StartupData/DataAsset_HeroStartUpData.h"
#include "HackAndSlash/CombatDebugHelper.h"

struct FInputActionValue;

void ACombatHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(!CharacterStartUpDataBase.IsNull()) //check if we have assigned a valid data asset to our soft reference
	{
		if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpDataBase.LoadSynchronous()) //we validate our load call
		{
			LoadedData->GiveToAbilitySystemComponent(CombatAbilitySystemComponent);
		}
	}
}

void ACombatHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))
}

void ACombatHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

