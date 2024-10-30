// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/CombatGameplayTags.h"


namespace CombatGameplayTags
{
	/** Input tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
					//Name of our input tag		Name in editor
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipSword, "InputTag.EquipSword");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipSword, "InputTag.UnequipSword");
	
	/** Player tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");
}
