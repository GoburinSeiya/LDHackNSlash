// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace CombatGameplayTags
{
	/** Input tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move); //Declare a gameplaytag
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipSword);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipSword);

	/** Player tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword); //tag used to register weapon
}
