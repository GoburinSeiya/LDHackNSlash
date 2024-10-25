// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"

// Sets default values
ACombatWeaponBase::ACombatWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

