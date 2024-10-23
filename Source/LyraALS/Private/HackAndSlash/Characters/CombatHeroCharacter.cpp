// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HackAndSlash/CombatDebugHelper.h"

void ACombatHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(TEXT("Working"));
}
