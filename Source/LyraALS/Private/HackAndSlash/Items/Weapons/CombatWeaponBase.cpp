// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ACombatWeaponBase::ACombatWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	SetRootComponent(WeaponStaticMesh);
	WeaponStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent()); //Set collision as child of root
	//Initialize some values
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}	



