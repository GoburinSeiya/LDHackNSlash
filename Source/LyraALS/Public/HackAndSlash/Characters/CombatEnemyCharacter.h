// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/Characters/CombatBaseCharacter.h"
#include "CombatEnemyCharacter.generated.h"

class UEnemyCombatComponent;


/**
 * 
 */
UCLASS()
class LYRAALS_API ACombatEnemyCharacter : public ACombatBaseCharacter
{
	GENERATED_BODY()

public:
	ACombatEnemyCharacter(); //We create a constructor
	
	//~ Begin IPawnCombatComponent Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatComponent Interface.

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	//We declare our combat component, dont forget to construct it in construction script
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

public:
	//Getter func
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}
	
private:
	void InitEnemyStartUpData();
	

	
};
