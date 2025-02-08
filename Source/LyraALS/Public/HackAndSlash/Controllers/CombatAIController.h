// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CombatAIController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAIPerceptionComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API ACombatAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACombatAIController(const FObjectInitializer& ObjectInitializer);
	
	//~ Begin IGenericTeamAgentInterface Interface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~ End IGenericTeamAgentInterface Interface

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* NPCPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* NPCSightConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Hearing* NPCHearingConfig;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus); //perception update delegate

private:
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAvoidance = true;

	//make it so that this variable can only be adjusted when bEnableCrowd... is true										this second meta specifier makes it a slider nice
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config", meta=(EditCondition="bEnableDetourCrowdAvoidance", UIMin = "1", UIMax = "4")) 
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoidance Config", meta=(EditCondition="bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;
	
};
