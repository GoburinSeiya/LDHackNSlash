// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatUIInterface.generated.h"

class UNPCUIComponent;
class UPawnUIComponent;
class UPlayerUIComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LYRAALS_API ICombatUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//pure function to get PawnUIComponent
	virtual UPawnUIComponent* GetPawnUIComponent() const = 0;

	virtual UPlayerUIComponent* GetPlayerUIComponent() const;

	virtual UNPCUIComponent* GetNPC_UIComponent() const;
};
