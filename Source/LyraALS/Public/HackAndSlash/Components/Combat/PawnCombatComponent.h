// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class ACombatWeaponBase;

/**
 * 
 */
UCLASS()
class LYRAALS_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapons")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, ACombatWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);
	/**							Tag of our weapon to register			Actual weapon						We use this to equip weapon through events, both for players and enemies **/
	
	UFUNCTION(BlueprintCallable, Category = "Combat|Weapons")
	ACombatWeaponBase* GetCharacterWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Combat|Weapons") //exposes variable to variable panel instead of detail panel with BlueprintReadWrite
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Combat|Weapons")
	ACombatWeaponBase* GetCharacterCurrentlyEquippedWeapon() const;
	
	
private:
	TMap<FGameplayTag, ACombatWeaponBase*> CharacterCarriedWeaponMap; /** This map will allow us to store multiple weapons that can be retrieved through a gameplay tag, remember a map is kind of like a dictionary
		an example, TMap<index, weapon*> would be a simpler way to do this, weapon is a pointer because we must reference it in memory **/
	
};
