// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include"HackAndSlash/CombatTypes/CombatEnumTypes.h"
#include "CombatGameplayAbility.generated.h"


class UPawnCombatComponent;
class UCombatAbilitySystemComponent;

UENUM() // property
enum class ECombatAbilityActivationPolicy : uint8 //enum
{
	OnTriggered, //enum components
	OnGiven
};

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbiliy Interface.(remember this is a convention)
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly, Category="CombatAbility") //property
	ECombatAbilityActivationPolicy AbilityActivationPolicy = ECombatAbilityActivationPolicy::OnTriggered; //define default value of our enum

	//Helper function to access PawnCombatComponent
	UFUNCTION(BlueprintPure, Category="Combat|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	//Helper function to access AbilitySystemComponent
	UFUNCTION(BlueprintPure, Category="Combat|Ability")
	UCombatAbilitySystemComponent* GetGameplayAbilityComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category="Combat|Ability", meta =(DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor",ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ECombatSuccessType& OutSuccessType);
};
