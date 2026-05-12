// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_ExecuteTaskOnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);

/**
 * 
 */
UCLASS()
class LYRAALS_API UAT_ExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()

UAT_ExecuteTaskOnTick();
	
public:
	UFUNCTION(BlueprintCallable, Category = "Combat|AbilityTasks", meta =(HidePin = "OwningAbility",
		DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UAT_ExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility); //static function needed

	//~ Begin UGameplayTask Interface
	
	/** Tick function for this task, if bTickingTask == true */
	virtual void TickTask(float DeltaTime) override;

	//~ End UGameplayTask Interface

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
};
