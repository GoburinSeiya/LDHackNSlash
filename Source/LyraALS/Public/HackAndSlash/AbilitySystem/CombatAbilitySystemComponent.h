// Fill out your copyright notice in the Description page of Project Settings.  

  

#pragma once  

#include "CoreMinimal.h"  
#include "AbilitySystemComponent.h"  
#include "HackAndSlash/CombatTypes/CombatStructTypes.h"  
#include "CombatAbilitySystemComponent.generated.h"  

  

/**  
* */  

UCLASS()  

class LYRAALS_API UCombatAbilitySystemComponent : public UAbilitySystemComponent  

{  

GENERATED_BODY()  

  

public:  
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);  
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);  

	//Create a helper func to grant default abilities on equip  
	// we can use meta specifier in U func to assign default values
	UFUNCTION(BlueprintCallable, Category = "Combat|Ability", meta = (ApplyLevel = 1))  
	void GrantHeroWeaponAbilities(const TArray<FCombatHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Combat|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Combat|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate); 
};  
