// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"
#include "CombatEnemyGameplayAbility.generated.h"

class ACombatEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatEnemyGameplayAbility : public UCombatGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Combat|Ability")
	ACombatEnemyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Combat|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<ACombatEnemyCharacter> CachedEnemyCharacter;
	
};
