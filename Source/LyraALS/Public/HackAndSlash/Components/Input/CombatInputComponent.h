// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "HackAndSlash/DataAssets/Input/DataAsset_InputConfig.h"
#include "CombatInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

	//We generate our own input binding method in this class

public:
	template<class UserObject, typename CallBackFunc>
	void  BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTags, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallBackFunc CallbackFunc);
	
};

template <class UserObject, typename CallBackFunc>
void UCombatInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTags, ETriggerEvent TriggerEvent, UserObject* ContextObject,
	CallBackFunc CallbackFunc)
{
	//check(InInputConfig); //We check if our pointer is valid, if not we create an assertion, and crash our editor on purpose
	checkf(InInputConfig, TEXT("Input config data asset is null, cannot proceed with binding")); // We check but we give ourselves more information, good practice fdr debbugging

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTags))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, CallbackFunc);
	}
}
