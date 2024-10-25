// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatHeroCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "HackAndSlash/DataAssets/Input/DataAsset_InputConfig.h"
#include "HackAndSlash/Components/Input/CombatInputComponent.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h" //include our ability system component

#include "HackAndSlash/CombatDebugHelper.h"

struct FInputActionValue;

void ACombatHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(CombatAbilitySystemComponent && CombatAbilitySystemComponent)
	{
		const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, Avatar Actor: %s"), *CombatAbilitySystemComponent->GetOwnerActor()->GetActorLabel(),
			*CombatAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		Debug::Print(TEXT("Ability system component valid") + ASCText + TEXT("\n"), FColor::Green);
		Debug::Print(TEXT("Attribute set valid") + ASCText, FColor::Green);
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

