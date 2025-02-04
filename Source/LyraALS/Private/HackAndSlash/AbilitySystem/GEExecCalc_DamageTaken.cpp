// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/GEExecCalc_DamageTaken.h"
#include "HackAndSlash/AbilitySystem/CombatAttributeSet.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/CombatDebugHelper.h"

struct FCombatDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(StanceDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	DECLARE_ATTRIBUTE_CAPTUREDEF(StanceDamageTaken)

	FCombatDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, StanceDamage, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, DamageTaken, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, StanceDamageTaken, Target, false)
	}
};

//Getter function for our struct
static const FCombatDamageCapture& GetCombatDamageCapture()
{
	static FCombatDamageCapture CombatDamageCapture;
	return CombatDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetCombatDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetCombatDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetCombatDamageCapture().StanceDamageDef);
	RelevantAttributesToCapture.Add(GetCombatDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//returns a const reference of type FGameplayEffectSpec, so we can access our tags
	const FGameplayEffectSpec& EffectSpec =  ExecutionParams.GetOwningSpec();

	//This are the things we set when setting the spec handle inside our gameplay ability, and we can retrieve it like so

	/*
	EffectSpec.GetContext().GetSourceObject();
	EffectSpec.GetContext().GetAbility();
	EffectSpec.GetContext().GetInstigator();
	EffectSpec.GetContext().GetEffectCauser();
	*/
	
	//To calculate we need to build an aggregator evaluator
	FAggregatorEvaluateParameters EvaluateParams;
	//We need to set two crucial variables for our Evaluator
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	//Attempts to calculate										which value we want to get				Tags				Variable to set
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetCombatDamageCapture().AttackPowerDef, EvaluateParams, SourceAttackPower);
	// Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);

	
	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	//We call the tmap where we place our elements inside the helper function
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(CombatGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			// Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(CombatGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}

		if (TagMagnitude.Key.MatchesTagExact(CombatGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			// Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}
	}
	
	float StanceDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetCombatDamageCapture().StanceDamageDef, EvaluateParams, StanceDamage);
	// Debug::Print(TEXT("SourceStanceDamage"), StanceDamage);
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetCombatDamageCapture().DefensePowerDef, EvaluateParams, TargetDefensePower);
	// Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		//We increase damage by 5% every subsequent hit after the first
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
		// Debug::Print(TEXT("ScaledBaseDamageLA"), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		//We increase damage by 15% every subsequent hit after the first
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;

		BaseDamage *= DamageIncreasePercentHeavy;
		// Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	// Debug::Print(TEXT("FinalDamage"), FinalDamageDone);
	const float FinalStanceDamageDone = BaseDamage * StanceDamage / TargetDefensePower;
	// Debug::Print(TEXT("FinalStanceDamage"), FinalStanceDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetCombatDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}

	if (FinalStanceDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetCombatDamageCapture().StanceDamageTakenProperty,
				EGameplayModOp::Override,
				FinalStanceDamageDone
				)
			);
	}
}
