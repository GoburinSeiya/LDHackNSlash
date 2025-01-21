// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Items/Weapons/CombatWeaponBase.h"
#include "Components/BoxComponent.h"

#include "HackAndSlash/CombatDebugHelper.h"

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
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void ACombatWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Get access to owner pawn
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn of the weapon: %s"), *GetName());

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(WeaponOwningPawn != HitPawn)
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}

		//TODO:Implement hit check for enemy characters
	}
}

void ACombatWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Get access to owner pawn
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf( WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn of the weapon: %s"), *GetName() );

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(WeaponOwningPawn != HitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}

		//TODO:Implement hit check for enemy characters
	}
}





