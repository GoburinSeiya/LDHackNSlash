// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
{
	for(const FHeroInputActionConfig& InputActionConfig : NativeInputActions) //we iterate through our input action array looking for the tag we receive as input
	{
		if(InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction) 
		{
			return InputActionConfig.InputAction; //if found we return the input action
		}
	}
	return nullptr; //else we return a null pointer
}
