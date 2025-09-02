// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Components/Combat/EnemyCombatComponent.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/CombatFunctionLibrary.h"

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
		bool bIsValidDeflect = false;

		const bool bIsPlayerBlocking = UCombatFunctionLibrary::NativeActorDoesHaveTag(HitActor, CombatGameplayTags::Player_Status_IsBlocking);
		const bool bPlayerDeflected = UCombatFunctionLibrary::NativeActorDoesHaveTag(HitActor,CombatGameplayTags::Player_Status_ActiveDeflectFrames);
		const bool bIsAttackUnblockable = false;
		const bool bIsPlayerDodgeing = false;
		const bool bIsAttackUndodgeable = false;

		if (bPlayerDeflected)
		{
			const FString DebugString = FString::Printf(TEXT("Deflect: %b %s"), bPlayerDeflected? TEXT("Valid Deflect") : TEXT("Invalid Deflect"));
			Debug::Print(DebugString, bPlayerDeflected? FColor::Green : FColor::Red);
			bIsValidDeflect = true;
		}

		else if (bIsPlayerBlocking && !bIsAttackUnblockable)
		{
			bIsValidBlock = UCombatFunctionLibrary::IsVectorPerpendicular(GetOwningPawn(), HitActor);	
		}
		
		else if (bIsPlayerDodgeing && bIsAttackUndodgeable)
		{
			//TODO:: validate dodge
		}

		FGameplayEventData EventData;
		EventData.Instigator = GetOwningPawn();
		EventData.Target = HitActor;
		
		if (bIsValidDeflect)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				HitActor,
				CombatGameplayTags::Shared_Event_Deflect,
				EventData
				);
		}
		else if (bIsValidBlock)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				HitActor,
				CombatGameplayTags::Player_Event_Blocked,
				EventData
				);
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
