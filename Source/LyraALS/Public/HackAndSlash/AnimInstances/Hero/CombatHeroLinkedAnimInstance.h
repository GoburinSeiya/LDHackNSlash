// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/AnimInstances/CombatBaseAnimInstance.h"
#include "CombatHeroLinkedAnimInstance.generated.h"

class UCombatHeroAnimInstance;

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatHeroLinkedAnimInstance : public UCombatBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe)) //what we do in BP marking functions as thread safe to call them in thread safe update
	UCombatHeroAnimInstance* GetCombatHeroAnimInstance() const;
};
