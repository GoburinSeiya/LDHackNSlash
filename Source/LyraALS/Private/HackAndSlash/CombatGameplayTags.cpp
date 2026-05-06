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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge, "InputTag.Dodge")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Block, "InputTag.Block")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock")

	/** Held abilities **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block")
	
	
	/** Player tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Sword, "Player.Weapon.Sword");

	/** Event tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Sword, "Player.Event.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Sword, "Player.Event.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_BeginBuffer, "Player.Event.BeginBuffer");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_WaitComboExecute, "Player.Event.WaitComboExecute");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Blocked, "Player.Event.Blocked");

	/** Player Ability Tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Sword, "Player.Ability.Equip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Sword, "Player.Ability.Unequip.Sword");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Sword, "Player.Ability.Attack.Light.Sword");  
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Sword, "Player.Ability.Attack.Heavy.Sword");
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Dodge, "Player.Ability.Dodge");
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
    UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");
    UE_DEFINE_GAMEPLAY_TAG(InputTag_Block_Released, "InputTag.Block.Released");
	
    UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
    UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");

	/** Player status tags **/
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher"); //tag used to jump to heavy combo end from light attacks
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_LiftoffCombo, "Player.Status.LiftoffCombo");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsHeavyAttacking, "Player.Status.IsHeavyAttacking"); 
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsLightAttacking, "Player.Status.IsLightAttacking");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsDodging, "Player.Status.IsDodging");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsBlocking, "Player.Status.IsBlocking");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsCharging, "Player.Status.IsCharging");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_ActiveDeflectFrames, "Player.Status.ActiveDeflectFrames");
	 UE_DEFINE_GAMEPLAY_TAG(Player_Status_IsTargeting, "Player.Status.IsTargeting");

	/** Enemy tags **/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_StanceBreak, "Shared.Ability.StanceBreak");

	/** Enemy status tags **/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	
	/** Shared event tags **/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light, "Shared.Event.HitReact.Light");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy, "Shared.Event.HitReact.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Slam, "Shared.Event.HitReact.Slam");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Deflect, "Shared.Event.Deflect");
	

	/** Shared set by caller tags **/
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_StanceDamage, "Shared.SetByCaller.StanceDamage");

	/** Shared ability tags **/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact_Light, "Shared.Ability.HitReact.Light");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact_Heavy, "Shared.Ability.HitReact.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact_Slam, "Shared.Ability.HitReact.Slam");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Deflect, "Shared.Ability.Deflect");
	
	/** Shared status tags **/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death");//this is the tag we should add when HP reaches 0
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_StanceBroken, "Shared.Status.StanceBroken"); //this is the tag we should add when Stance reaches it's limit
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	
	 
	
}
