// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Controllers/CombatAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "HackAndSlash/CombatDebugHelper.h"

ACombatAIController::ACombatAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	NPCSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("NPCSenseConfig_Sight");
	NPCHearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("NPCSenseConfig_Hearing");
	NPCPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("NPCPerceptionComponent");

	//Sight config
	NPCSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	NPCSightConfig->DetectionByAffiliation.bDetectFriendlies = false; //we can only see hostile pawns
	NPCSightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	NPCSightConfig->SightRadius = 5000.f;
	NPCSightConfig->LoseSightRadius = 0.f; //enemies never lose sight of player, might need to change this depending on the enmy type
	NPCSightConfig->PeripheralVisionAngleDegrees = 360.f; // vision angle, for combat enemies like bosses or high paced battles this works best with 360 vision so we never lose sight, reduce for stealth

	//Hearing config
	NPCHearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	NPCHearingConfig->DetectionByAffiliation.bDetectFriendlies = false;
	NPCHearingConfig->DetectionByAffiliation.bDetectNeutrals = true; //we want our npc to hear only the player and misc distractions, again tune this depending on the enmy type specifically can be modified in bp
	NPCHearingConfig->HearingRange = 750.f;

	//Perception config
	NPCPerceptionComponent->ConfigureSense(*NPCSightConfig);
	NPCPerceptionComponent->ConfigureSense(*NPCHearingConfig);
	NPCPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	NPCPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated); //delegate we need to bind functions to

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ACombatAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent =  Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	/** We check if the other team agent ID is not equal to this AI team ID */
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		//This means the pawn is an enemy
		return ETeamAttitude::Hostile;
	}

	//TODO: We need to add logic for neutral hearing, for distractions
	
	return ETeamAttitude::Friendly;
}

void ACombatAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		// Debug::Print(("CrowdFollowingComponent is valid"), FColor::Green);
		/** values that vince found have more impact on avoidance quality */
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAvoidance? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled); //used to toggle avoidance on and off, we'll create a bool for this

		switch (DetourCrowdAvoidanceQuality)
		{
		case 1:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		default:
			break;
		}

		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
		
	}
}

void ACombatAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		// Debug::Print(Actor->GetActorNameOrLabel() + TEXT(" was sensed"), FColor::Blue);
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			//Set a bb value							key name must be identical, then value
			BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
