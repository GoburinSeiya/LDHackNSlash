// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYRAALS_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T> //common naming convention for a template function
	T* GetOwningPawn() const //helps us get the owning pawn of our base component, and helps us in directly casting to the type we want
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template parameter get Pawn must be derived from Pawn class"); //allows us to assertain wether our cast was or not correct
		return CastChecked<T>(GetOwner()); //We are casting to our owner, we validate this cast, we use this function if we need to cast to a specific type, like player or enemy
	}

	APawn* GetOwningPawn() const //helper function to get owner pawn
	{
		return GetOwningPawn<APawn>(); //We use this function to cast when we do not need to cast to a specific type
	}
	
	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template parameter GetOwnerController must be derived from AController class");
		return GetOwningPawn<APawn>()->GetController<T>;
	}
};
