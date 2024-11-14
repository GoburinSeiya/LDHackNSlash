// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"  
#include "CombatAttributeSet.generated.h"

//Go to UAtrribbuteSet definition, and search for helper func, add into your own attribute class
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCombatAttributeSet();

	//This is how we define an attribute
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxHealth)


	//Rage attributes
	UPROPERTY(BlueprintReadOnly, Category="CinderOfKings")
	FGameplayAttributeData CurrentCinderCharge;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, CurrentCinderCharge)

	UPROPERTY(BlueprintReadOnly, Category="CinderOfKings")
	FGameplayAttributeData MaxCinderCharge;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxCinderCharge)
	
	//Stance attributes
	UPROPERTY(BlueprintReadOnly, Category="StanceBreak")
	FGameplayAttributeData CurrentStanceLevel;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, CurrentStanceLevel)

	UPROPERTY(BlueprintReadOnly, Category="StanceBreak")
	FGameplayAttributeData MaxStanceLevel;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxStanceLevel)

	//Damage attributes
	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData StanceDamage;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, StanceDamage)

	UPROPERTY(BlueprintReadOnly, Category="Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, DefensePower)
};
