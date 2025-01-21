// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/DataAssets/StartupData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpDataBase.generated.h"

class UCombatEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class LYRAALS_API UDataAsset_EnemyStartUpDataBase : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	//Create an array of our Gameplay Ability class 
	UPROPERTY(EditDefaultsOnly, Category = "StarUpData")
	TArray< TSubclassOf<UCombatEnemyGameplayAbility> > EnemyCombatAbilities;
};
