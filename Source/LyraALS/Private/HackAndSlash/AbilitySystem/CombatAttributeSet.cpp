// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/CombatAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "HackAndSlash/CombatFunctionLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "HackAndSlash/Interfaces/CombatUIInterface.h"
#include "HackAndSlash/Components/UI/PawnUIComponent.h"
#include "HackAndSlash/Components/UI/PlayerUIComponent.h"

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
	// //Get a hold of our UI interface
	// ICombatUIInterface* PawnUI_Interface = Cast<ICombatUIInterface>(Data.Target.GetAvatarActor());

	if (!CachedCombatUIInterface.IsValid())
		CachedCombatUIInterface = TWeakInterfacePtr<ICombatUIInterface>(Data.Target.GetAvatarActor());

	checkf(CachedCombatUIInterface.IsValid(), TEXT("%s did not implement UI interface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedCombatUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	// These checks are to clamp the values of our attributes to 0 or their max value so we dont get funny behaviour
	// this ifs only fire if the attribute is the one being evaluated this frame, this is why every evaluated value
	// should be locked in this checks
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentCinderChargeAttribute())
	{
		const float NewCurrentCinderCharge = FMath::Clamp(GetCurrentCinderCharge(), 0.f, GetMaxCinderCharge());
		SetCurrentCinderCharge(NewCurrentCinderCharge);
		if (UPlayerUIComponent* PlayerUIComponent = CachedCombatUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentCindersChanged.Broadcast(GetCurrentCinderCharge()/GetMaxCinderCharge());
		}
	}

	if (Data.EvaluatedData.Attribute == GetMaxStanceLevelAttribute())
	{
		const float NewCurrentStanceLevel = FMath::Clamp(GetCurrentStanceLevel(), 0.f, GetMaxStanceLevel());
		SetCurrentStanceLevel(NewCurrentStanceLevel);
		PawnUIComponent->OnStanceLevelChanged.Broadcast(GetCurrentStanceLevel()/GetMaxStanceLevel());
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

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
		
		if (GetCurrentHealth() == 0.f)
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

		PawnUIComponent->OnStanceLevelChanged.Broadcast(GetCurrentStanceLevel()/GetMaxStanceLevel());
		
		if (GetCurrentStanceLevel() >= GetMaxStanceLevel())
		{
			UCombatFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), CombatGameplayTags::Shared_Status_StanceBroken);
		}
	}
}
