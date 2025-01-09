// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/AnimInstances/CombatCharacterAnimInstance.h"
#include "CombatHeroAnimInstance.generated.h"

class ACombatHeroCharacter;

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatHeroAnimInstance : public UCombatCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	ACombatHeroCharacter* OwningHeroCharacter;
};
