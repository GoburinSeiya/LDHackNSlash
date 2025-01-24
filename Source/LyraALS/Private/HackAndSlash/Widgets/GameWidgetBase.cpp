// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Widgets/GameWidgetBase.h"
#include "HackAndSlash/Interfaces/CombatUIInterface.h"


void UGameWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ICombatUIInterface* PawnUI_Interface = Cast<ICombatUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent*  HeroUIComponent = PawnUI_Interface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInit(HeroUIComponent);
		}
	}
}

void UGameWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (ICombatUIInterface* PawnUI_Interface = Cast<ICombatUIInterface>(OwningEnemyActor))
	{
		UNPCUIComponent* NPC_UIComponent = PawnUI_Interface->GetNPC_UIComponent();

		checkf(NPC_UIComponent, TEXT("Failed to extract an UI component from npc %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningNPCUIComponentInit(NPC_UIComponent);
	}
}
