// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HackAndSlash/AbilitySystem/Abilities/CombatEnemyGameplayAbility.h"
#include "HackAndSlash/Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "HackAndSlash/DataAssets/StartupData/DataAsset_EnemyStartUpDataBase.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "HackAndSlash/Components/UI/NPCUIComponent.h"


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

	NPC_UIComponent = CreateDefaultSubobject<UNPCUIComponent>("NPC_UIComponent");
	
}

UPawnCombatComponent* ACombatEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* ACombatEnemyCharacter::GetPawnUIComponent() const
{
	return NPC_UIComponent;
}

UNPCUIComponent* ACombatEnemyCharacter::GetNPC_UIComponent() const
{
	return NPC_UIComponent;
}

void ACombatEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

void ACombatEnemyCharacter::InitEnemyStartUpData()
{
	if(CharacterStartUpDataBase.IsNull())
		return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpDataBase.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpDataBase.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(CombatAbilitySystemComponent);
				}
			}
			//[]	capture list () func inputs {} body
			) //nameless func that we can declare and define in the same line
		);
}
