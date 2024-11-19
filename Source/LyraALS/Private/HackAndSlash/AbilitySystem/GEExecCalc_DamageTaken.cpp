// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/GEExecCalc_DamageTaken.h"
#include "HackAndSlash/AbilitySystem/CombatAttributeSet.h"

struct FCombatDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(StanceDamage)

	FCombatDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCombatAttributeSet, StanceDamage, Source, false)
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
}
