// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"
#include "CombatStructTypes.generated.h"

class UCombatHeroLinkedAnimInstance; 
class UCombatHeroGameplayAbility;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FCombatHeroAbilitySet
{
	GENERATED_BODY()
	//Define important variables for our struct
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; //dont forget to add header file

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UCombatHeroGameplayAbility> AbilityToGrant;
	
	//validate helper func
	/** why do we do this? what we want to validate is AbilityToGrant, to do this by other means would require the header file, this is something we do not want to do inside a header file,
	 its a bad practice, possible tho, hence this function to skip over this requirement and use the header file in the cpp file... so u know, include that too**/ 
	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FCombatHeroWeaponData
{
	GENERATED_BODY()

	//Variable declaration to get our anim instance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UCombatHeroLinkedAnimInstance> WeaponAnimInstanceToLink;

	//Array to store weapon unique abilities
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty="InputTag"))
	TArray<FCombatHeroAbilitySet> DefaultWeaponAbilities;

	//Weapon unique IMC
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty="InputTag"))
	UInputMappingContext* WeaponInputMappingContext;
};

