// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatBaseCharacter.h"

// Sets default values
ACombatBaseCharacter::ACombatBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//Disable ticking if not needed, if you ever find you do, reenable
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false; //make our decals affect the ground only, not our character mesh
}



