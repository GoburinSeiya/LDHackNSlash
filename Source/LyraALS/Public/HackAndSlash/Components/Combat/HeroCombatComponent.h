// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class ACombatHeroWeapon;

/**
 * 
 */
UCLASS()
class LYRAALS_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	//func to get weapon by tag, parent already has access to FGameplayTag so no need to include its header file
	UFUNCTION(BlueprintCallable, Category = "Combat")
	ACombatHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
	
};
