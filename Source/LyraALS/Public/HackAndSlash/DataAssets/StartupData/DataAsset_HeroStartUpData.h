// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/DataAssets/StartupData/DataAsset_StartUpDataBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FCombatHeroAbilitySet
{
	GENERATED_BODY()
	//Define important variables for our struct
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; //dont forget to add header file

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UCombatGameplayAbility> AbilityToGrant;
	
	//validate helper func
	/** why do we do this? what we want to validate is AbilityToGrant, to do this by other means would require the header file, this is something we do not want to do inside a header file,
	 its a bad practice, possible tho, hence this function to skip over this requirement and use the header file in the cpp file... so u know, include that too**/ 
	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class LYRAALS_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UCombatAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override; /** we create a function to define abilities, the input can be used to determine many things like
	difficulty, cost, etc. **/
	
private:
	//We create an array for our abilities, those we are granting at startup
	UPROPERTY(EditDefaultsOnly, Category = "StarUpData", meta=(TitleProperty = "InputTag"))
	TArray<FCombatHeroAbilitySet> HeroStartUpAbilitySets;
};
