// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Characters/CombatBaseCharacter.h"
#include "CombatHeroCharacter.generated.h"

class UDataAsset_InputConfig;
class UHeroCombatComponent; //forward declare component

/**
 * 
 */
UCLASS()
class LYRAALS_API ACombatHeroCharacter : public ACombatBaseCharacter
{
	GENERATED_BODY()

public:
	ACombatHeroCharacter();
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override; //Setup our player input component
	virtual void BeginPlay() override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent; 
#pragma endregion Components
	
#pragma region Inputs
	//			Accessibility	Editability in BP	Where to save variable	meta access
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset; //We bind our input config
#pragma endregion

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; } //Combat component getter function
};
