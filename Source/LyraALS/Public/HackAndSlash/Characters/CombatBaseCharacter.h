// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HackAndSlash/Interfaces/PawnCombatInterface.h"
#include "CombatBaseCharacter.generated.h"


class UCombatAbilitySystemComponent;
class UCombatAttributeSet;
class UDataAsset_StartUpDataBase;
UCLASS()
class LYRAALS_API ACombatBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatBaseCharacter();
	
	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface.
	
	//~ Begin IPawnCombatComponent Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatComponent Interface.
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UCombatAbilitySystemComponent* CombatAbilitySystemComponent; //we create our combat ability system component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UCombatAttributeSet* CombatAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpDataBase;

public:
	//We create public geters to get direct access in C++
	FORCEINLINE UCombatAbilitySystemComponent* GetCombatAbilitySystemComponent() const { return CombatAbilitySystemComponent; }

	FORCEINLINE UCombatAttributeSet* GetCombatAttributeSet() const { return CombatAttributeSet; }


};
