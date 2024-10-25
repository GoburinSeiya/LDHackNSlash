// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

//Declaration of a Struct
USTRUCT(BlueprintType)
struct FHeroInputActionConfig
{
	GENERATED_BODY() //Macro to generate the body of our struct, without it we cant compile

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;
};

/**
 * 
 */
UCLASS()
class LYRAALS_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext; //Create a IMC

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
													//with this meta declaration the name of our rows will be the name of our input actions which is convenient
	TArray<FHeroInputActionConfig> NativeInputActions; //We create a array for our InputActions

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const; //We create a function to bind our inputs properly
};
