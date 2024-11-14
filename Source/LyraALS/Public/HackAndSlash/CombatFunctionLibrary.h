// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HackAndSlash/CombatTypes/CombatEnumTypes.h"
#include "CombatFunctionLibrary.generated.h"

class UCombatAbilitySystemComponent;
class UPawnCombatComponent;

/**
 * 
 */
UCLASS()
class LYRAALS_API UCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UCombatAbilitySystemComponent* NativeGetCombatASCFromActor(AActor* InActor);

	static bool NativeActorDoesHaveTag(AActor* InActor, FGameplayTag InTagToCheck);

	UFUNCTION(BlueprintCallable, Category="Combat|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTagToAdd);

	UFUNCTION(BlueprintCallable, Category="Combat|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InTagToRemove);

	//This will be a BP only func, for this kind of funcs well use the prefix BP_;
	UFUNCTION(BlueprintCallable, Category="Combat|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
																				//this meta specifier allows us to choose the name displayed in editor;
																													//this one having multiple execute pins from our declared enum;
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InTagToCheck, ECombatConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="Combat|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ECombatValidType& OutValidType);
};
