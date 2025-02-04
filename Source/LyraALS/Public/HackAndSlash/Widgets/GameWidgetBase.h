// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidgetBase.generated.h"

class UNPCUIComponent;
class UPlayerUIComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API UGameWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningPlayerUIComponentInit"))
	void BP_OnOwningPlayerUIComponentInit(UPlayerUIComponent* OwningHeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnOwningNPC_UIComponentInit"))
	void BP_OnOwningNPCUIComponentInit(UNPCUIComponent* OwningNPC_UIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
	
	
};
