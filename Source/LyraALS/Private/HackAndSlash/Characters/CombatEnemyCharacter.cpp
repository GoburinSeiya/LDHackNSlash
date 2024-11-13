// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatEnemyGameplayAbility.h"
#include "HackAndSlash/Components/Combat/EnemyCombatComponent.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatEnemyGameplayAbility.h"


ACombatEnemyCharacter::ACombatEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; //make sure or IA is possesed wether its placed or spawned

	//Initialize controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Initialize movement variables for enemies, don't forget to add header file to access these variables
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	//Construct our componets
	//												name
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
	
}
