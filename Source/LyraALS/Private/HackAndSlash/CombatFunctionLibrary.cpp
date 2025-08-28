// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/CombatFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h"  
#include "HackAndSlash/Components/Combat/PawnCombatComponent.h"
#include "HackAndSlash/Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "GenericTeamAgentInterface.h"

UCombatAbilitySystemComponent* UCombatFunctionLibrary::NativeGetCombatASCFromActor(AActor* InActor)
{
	check(InActor);
	
	/** after validation we need to extract the asc from our actor, UE has this func already, so we must call it, to do so include AbilitySystemBlueprintLibrary.h; **/
	return CastChecked<UCombatAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UCombatFunctionLibrary::NativeActorDoesHaveTag(AActor* InActor, FGameplayTag InTagToCheck)
{
	UCombatAbilitySystemComponent* ASC = NativeGetCombatASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(InTagToCheck);
}

void UCombatFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTagToAdd)
{
	//Local variable to store the ASC
	UCombatAbilitySystemComponent* ASC = NativeGetCombatASCFromActor(InActor);

	//If our actor does not have the tag we add it
	if(!ASC->HasMatchingGameplayTag(InTagToAdd))
	{
		ASC->AddLooseGameplayTag(InTagToAdd);
	}
}

void UCombatFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InTagToRemove)
{
	UCombatAbilitySystemComponent* ASC = NativeGetCombatASCFromActor(InActor);

	//if our actor has the gameplay tag, then remove it
	if(ASC->HasMatchingGameplayTag(InTagToRemove))
	{
		ASC->RemoveLooseGameplayTag(InTagToRemove);
	}
}

void UCombatFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InTagToCheck,
	ECombatConfirmType& OutConfirmType)
{
	//					if actor hast tag c++ func					return enum as yes			return enum no if false
	OutConfirmType = NativeActorDoesHaveTag(InActor, InTagToCheck)? ECombatConfirmType::Yes : ECombatConfirmType::No;
}

UPawnCombatComponent* UCombatFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UCombatFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	ECombatValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent? ECombatValidType::Valid : ECombatValidType::Invalid;

	return CombatComponent;
}

bool UCombatFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn);
	check(TargetPawn);
	
	//We use the generic team agent interface to check if a pawn is hostile, include header file
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UCombatFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UCombatFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InHitActor,
	float& OutAngleDifference)
{
	check(InAttacker && InHitActor);

	const FVector HitActorForward = InHitActor->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InHitActor->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(HitActorForward, VictimToAttackerNormalized);

	//The result is in rad, we need to convert it to deg
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(HitActorForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
		OutAngleDifference *= -1.f;

	if (OutAngleDifference >- -45.f && OutAngleDifference <= 45.f)
	{
		return CombatGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return CombatGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return CombatGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return CombatGameplayTags::Shared_Status_HitReact_Right;
	}
	
	return CombatGameplayTags::Shared_Status_HitReact_Front;
}
