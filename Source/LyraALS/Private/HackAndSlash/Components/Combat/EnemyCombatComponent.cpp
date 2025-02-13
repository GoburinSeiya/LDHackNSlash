// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Components/Combat/EnemyCombatComponent.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (HitActor)
	{
		// Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" is hitting: ") + HitActor->GetActorNameOrLabel());
		if (OverlappedActors.Contains(HitActor))
			return;

		OverlappedActors.AddUnique(HitActor);

		//Here we'll have to process player block

		//TODO:: Implement block check
		bool bIsValidBlock = false;
		bool bIsValidDodge = false;

		const bool bIsPlayerBlocking = false;
		const bool bIsAttackUnblockable = false;
		const bool bIsPlayerDodgeing = false;
		const bool bIsAttackUndodgeable = false;

		if (bIsPlayerBlocking && !bIsAttackUnblockable)
		{
			//TODO:: validate block			
		}

		if (bIsPlayerDodgeing && bIsAttackUndodgeable)
		{
			//TODO:: validate dodge
		}

		FGameplayEventData EventData;
		EventData.Instigator = GetOwningPawn();
		EventData.Target = HitActor;

		if (bIsValidBlock)
		{
			//TODO:: Handle block
		}
		else if (bIsValidDodge)
		{
			//TODO:: we let the animation play and let the dodge handle the rest
		}
		else
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				GetOwningPawn(), //pawn to send the event to
				CombatGameplayTags::Shared_Event_MeleeHit, //tag to send
				EventData //event data, construct one with FGameplayData
				);
		}
	}
}
