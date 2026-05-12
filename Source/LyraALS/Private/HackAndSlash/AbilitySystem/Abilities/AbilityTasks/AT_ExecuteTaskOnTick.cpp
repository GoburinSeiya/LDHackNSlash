// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/Abilities/AbilityTasks/AT_ExecuteTaskOnTick.h"

UAT_ExecuteTaskOnTick::UAT_ExecuteTaskOnTick()
{
	bTickingTask = true;
}

UAT_ExecuteTaskOnTick* UAT_ExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UAT_ExecuteTaskOnTick* Node = NewAbilityTask<UAT_ExecuteTaskOnTick>(OwningAbility);

	return Node;
}

void UAT_ExecuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	//this check should always be included for GAS in this kind of abilities, as it checks if the ability is still active
	//before broadcast
	if (ShouldBroadcastAbilityTaskDelegates())
		OnAbilityTaskTick.Broadcast(DeltaTime);
	else
		EndTask();
}
