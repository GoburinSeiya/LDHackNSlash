// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatGameplayAbility.h"
#include "CombatHeroGameplayAbility.generated.h"

class ACombatHeroCharacter;
class ACombatHeroController;
class UHeroCombatComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatHeroGameplayAbility : public UCombatGameplayAbility
{
	GENERATED_BODY()

public:
	//Helper function to get our hero character, this one isnt const, check in definition
	UFUNCTION(BlueprintPure, Category = "Combat|Ability")
	ACombatHeroCharacter* GetHeroCharacterFromActorInfo();

	//Helper funtion to get player controller
	UFUNCTION(BlueprintPure, Category = "Combat|Ability")
	ACombatHeroController* GetHeroControllerFromActorInfo();

	//Helper function to get player combat component
	UFUNCTION(BlueprintPure, Category = "Combat|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Combat|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageSpecHandle ( TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
		int32 InCurrentComboCount);
	
private:
	//We make a member variable to store our Avatar actor info cast from the Getter function
	TWeakObjectPtr<ACombatHeroCharacter> CachedHeroCharacter;
	//this is a unreal unique type of smart pointer, instead of keeping the object alive it simply holds a reference to it, good when we need a reference to an object but not increasing its ref count

	//We cache our controller
	TWeakObjectPtr<ACombatHeroController> CachedHeroController;
};
