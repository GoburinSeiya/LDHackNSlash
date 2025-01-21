// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HackAndSlash/AnimInstances/CombatBaseAnimInstance.h"
#include "CombatCharacterAnimInstance.generated.h"

class  ACombatBaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatCharacterAnimInstance : public UCombatBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	ACombatBaseCharacter* OwningCharacter;
	
	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent; //property access

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bHasAcceleration;
};
