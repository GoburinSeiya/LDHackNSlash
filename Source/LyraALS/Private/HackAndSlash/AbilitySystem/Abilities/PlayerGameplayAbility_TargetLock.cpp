// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/AbilitySystem/Abilities/PlayerGameplayAbility_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HackAndSlash/Characters/CombatHeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HackAndSlash/Widgets/GameWidgetBase.h"
#include "HackAndSlash/Controllers/CombatHeroController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "HackAndSlash/CombatFunctionLibrary.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/CombatDebugHelper.h"

void UPlayerGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	CleanUpTargetLock();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedOnActor || UCombatFunctionLibrary::NativeActorDoesHaveTag(CurrentLockedOnActor,
		CombatGameplayTags::Shared_Status_Death) || UCombatFunctionLibrary::NativeActorDoesHaveTag(GetHeroCharacterFromActorInfo(),
			CombatGameplayTags::Shared_Status_Death))
	{
		CancelTargetLock();
		return;
	}

	SetTargetLockWidgetPosition();
}

void UPlayerGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableTargets();

	if (AvailableLockOnActors.IsEmpty())
	{
		CancelTargetLock();
		return;
	}

	CurrentLockedOnActor = GetNearestTargetFromAvailableActors(AvailableLockOnActors);

	if (CurrentLockedOnActor)
	{
		Debug::Print("Current lock on target: " + CurrentLockedOnActor->GetActorNameOrLabel(),FColor::Purple);

		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
		CancelTargetLock();
}

void UPlayerGameplayAbility_TargetLock::GetAvailableTargets()
{
	TArray<FHitResult> BoxHitResults;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(), 
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		ActorsToIgnore,
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent  : EDrawDebugTrace::None,
		BoxHitResults,
		true
		);
	for (const FHitResult& TraceHit : BoxHitResults)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				AvailableLockOnActors.AddUnique(HitActor);
				
				Debug::Print(HitActor->GetActorNameOrLabel());
			}
		}
	}
}

AActor* UPlayerGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	
	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(),
		InAvailableActors,
		ClosestDistance);
	
}

void UPlayerGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign valid widget class in the BP system"));

		DrawnTargetLockWidget = CreateWidget<UGameWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);

		DrawnTargetLockWidget->AddToViewport();
	}
}

void UPlayerGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedOnActor)
	{
		CancelTargetLock();
		return;
	}
	FVector2D ScreenPos = FVector2D::ZeroVector;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetHeroControllerFromActorInfo(), //Owner controller
		CurrentLockedOnActor->GetActorLocation(), //Target location
		ScreenPos, // Out parameter (projected screen position)
		true // bIs it relative to viewport?
		);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		//Adjust to center of target
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget)) //dont forget header file
				{
					TargetLockWidgetSize.X =  FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		); //include widget tree header file
	}

	ScreenPos -=(TargetLockWidgetSize / 2.f); //adjust widget size to screen
	//ScreenPos.Y -= 50.f; //height offset test
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPos, false);
}

void UPlayerGameplayAbility_TargetLock::CancelTargetLock()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UPlayerGameplayAbility_TargetLock::CleanUpTargetLock()
{
	AvailableLockOnActors.Empty();

	CurrentLockedOnActor = nullptr;

	if (DrawnTargetLockWidget)
		DrawnTargetLockWidget->RemoveFromParent();

	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}
