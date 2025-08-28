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
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Sword);  
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Sword);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Dodge);  
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Block);

	/** Held abilities **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);


	/** Player tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword); //tag used to register weapon
	
	/** Event tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword); //tag used to send event of equipping weapon
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword); //tag used to send event of unequipping weapon
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_BeginBuffer);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_WaitComboExecute);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	/** Player Ability Tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Sword);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);  
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Dodge);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);

	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	/** Player status tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher); //tag used to jump to heavy combo end from light attacks
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_LiftoffCombo);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsHeavyAttacking);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsLightAttacking);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsDodging);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsBlocking);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_IsCharging);
	

	
	/** Enemy tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon); //tag used to register weapon
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	
	/** Enemy Status Tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	
	
	/** Shared event tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact_Light);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact_Heavy);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact_Slam);
	
	

	/** Shared set by caller tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_StanceDamage);

	/** Shared ability tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact_Light);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact_Heavy);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact_Slam);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_StanceBreak);

	/** Shared status tags **/
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Death); //this is the tag we should add when HP reaches 0
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_StanceBroken); //this is the tag we should add when Stance reaches it's limit
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Strafing);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	LYRAALS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
	
	
	
}
