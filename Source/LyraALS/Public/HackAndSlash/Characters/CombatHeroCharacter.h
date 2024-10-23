// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Characters/CombatBaseCharacter.h"
#include "CombatHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LYRAALS_API ACombatHeroCharacter : public ACombatBaseCharacter
{
	GENERATED_BODY()

public:


protected:
	virtual void BeginPlay() override;

private:

};
