// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/CombatAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "HackAndSlash/CombatFunctionLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/CombatDebugHelper.h"

UCombatAttributeSet::UCombatAttributeSet()
{
	//Health variables init
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);

	//rage variables init
	InitCurrentCinderCharge(1.f);
	InitMaxCinderCharge(1.f);

	//Combat variables init
	InitAttackPower(1.f);
	InitDefensePower(1.f);

	//Stance variables init
	InitCurrentStanceLevel(1.f);
	InitMaxStanceLevel(1.f);
	InitStanceDamage(1.f);
}

void UCombatAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentCinderChargeAttribute())
	{
		const float NewCurrentCinderCharge = FMath::Clamp(GetCurrentCinderCharge(), 0.f, GetMaxCinderCharge());
		SetCurrentCinderCharge(NewCurrentCinderCharge); 
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		//Debug
		 const FString HealthDebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, New Current Health: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		 );

		Debug::Print(HealthDebugString, FColor::Green);
		
		//TODO:: Notify the UI
		
		if (NewCurrentHealth == 0.f)
		{
			UCombatFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), CombatGameplayTags::Shared_Status_Death);
		}
	}

	if (Data.EvaluatedData.Attribute == GetStanceDamageTakenAttribute())
	{
		const float OldStanceLevel = GetCurrentStanceLevel();
		const float StanceDamageDone = GetStanceDamageTaken();

		const float NewStanceLevel = FMath::Clamp(OldStanceLevel + StanceDamageDone, 0.f, GetMaxStanceLevel());
		SetCurrentStanceLevel(NewStanceLevel);

		//Debug
		const FString StanceDebugString = FString::Printf(
			TEXT("Old Stance Level: %f, Stance Damage Done: %f, New Stance Level: %f"),
			OldStanceLevel,
			StanceDamageDone,
			NewStanceLevel
		);

		Debug::Print(StanceDebugString, FColor::Yellow);

		//TODO:: Notify the UI

		if (NewStanceLevel >= GetMaxStanceLevel())
		{
			UCombatFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), CombatGameplayTags::Shared_Status_StanceBroken);
		}
	}
}
