// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Components/Combat/HeroCombatComponent.h"
#include "HackAndSlash/Items/Weapons/CombatHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"

#include "HackAndSlash/CombatDebugHelper.h"

ACombatHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<ACombatHeroWeapon>(GetCharacterWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor))
		return;

	OverlappedActors.AddUnique(HitActor);

	//Construct gameplay event data to fill in our SendGameplayEvent Function
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		CombatGameplayTags::Shared_Event_MeleeHit,
		EventData
	);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}
