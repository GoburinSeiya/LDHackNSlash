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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Sword, "InputTag.LightAttack.Sword");  
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Sword, "InputTag.HeavyAttack.Sword")
	
	/** Player tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

	/** Event tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Sword, "Player.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Sword, "Player.Event.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_BeginBuffer, "Player.Event.BeginBuffer");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_WaitComboExecute, "Player.Event.WaitComboExecute");

	/** Player Ability Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Sword, "Player.Ability.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword, "Player.Ability.Attack.Light.Sword");  
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword, "Player.Ability.Attack.Heavy.Sword");

	/** Player status tags **/
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher"); //tag used to jump to heavy combo end from light attacks
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_LiftoffCombo, "Player.Status.LiftoffCombo");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsHeavyAttacking, "Player.Status.IsHeavyAttacking");
}
