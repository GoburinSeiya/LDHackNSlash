// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UCombatGameplayAbility;
class UCombatAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API UDataAsset_StartUpDataBase : public UDataAsset
{	
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1); /** we create a function to define abilities, the input can be used to determine many things like
	difficulty, cost, etc. **/
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StarUpData")
	TArray< TSubclassOf<UCombatGameplayAbility>> ActivateOnGivenAbilities; //Array to store abilities that must be activated OnGiven
	UPROPERTY(EditDefaultsOnly, Category = "StarUpData")
	TArray< TSubclassOf<UCombatGameplayAbility>> ReactiveAbilities; //Array to store abilities that must be activated on hit or on death, that are triggered upon certain conditions

	//function to grant ability
	void GrantAbilities(const TArray< TSubclassOf<UCombatGameplayAbility>>& InAbilitiesToGive, UCombatAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
