// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class LYRAALS_API ACombatWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatWeaponBase();

protected:
	//Weapon Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponStaticMesh;
	//Collision detection
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

public:
	//We create our public getters
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const{return WeaponCollisionBox;}
};
