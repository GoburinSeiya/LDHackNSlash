// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"
#include "HackAndSlash/CombatTypes/CombatStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "CombatHeroWeapon.generated.h"


/**
 * 
 */
UCLASS()
class LYRAALS_API ACombatHeroWeapon : public ACombatWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FCombatHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	//getter func
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
	
};
