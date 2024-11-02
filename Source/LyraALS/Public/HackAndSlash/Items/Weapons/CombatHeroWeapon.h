// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"
#include "HackAndSlash/CombatTypes/CombatStructTypes.h"
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
	
};
