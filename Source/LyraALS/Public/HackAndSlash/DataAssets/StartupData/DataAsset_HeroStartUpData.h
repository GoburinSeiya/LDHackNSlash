// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/DataAssets/StartupData/DataAsset_StartUpDataBase.h"
#include "HackAndSlash/CombatTypes/CombatStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"

/**
 * 
 */
UCLASS()
class LYRAALS_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override; /** we create a function to define abilities, the input can be used to determine many things like
	difficulty, cost, etc. **/
	
private:
	//We create an array for our abilities, those we are granting at startup
	UPROPERTY(EditDefaultsOnly, Category = "StarUpData", meta=(TitleProperty = "InputTag"))
	TArray<FCombatHeroAbilitySet> HeroStartUpAbilitySets;
};
