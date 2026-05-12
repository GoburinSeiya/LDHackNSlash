// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatHeroGameplayAbility.h"
#include "PlayerGameplayAbility_TargetLock.generated.h"

class UGameWidgetBase;

/**
 * 
 */
UCLASS()
class LYRAALS_API UPlayerGameplayAbility_TargetLock : public UCombatHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	
	//interface comment
	
	//~ Begin UGameplayAbility Interface
	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	//~ End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

private:
	void TryLockOnTarget();
	void GetAvailableTargets();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	
	void CancelTargetLock();
	void CleanUpTargetLock();

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);
	
	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TArray< TEnumAsByte <EObjectTypeQuery> > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	bool bShowPersistentDebugShape = false;

	//This is a hard reference, good since this is a key asset, with a low mem cost and will be used often, we want it in memory
	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TSubclassOf<UGameWidgetBase> TargetLockWidgetClass;

	UPROPERTY()
	TArray<AActor*> AvailableLockOnActors;

	UPROPERTY()
	AActor* CurrentLockedOnActor;

	UPROPERTY()
	UGameWidgetBase* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

};
