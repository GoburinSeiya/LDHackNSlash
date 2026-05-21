// Fill out your copyright notice in the Description page of Project Settings.


#include "HackAndSlash/Characters/CombatHeroCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "HackAndSlash/DataAssets/Input/DataAsset_InputConfig.h"
#include "HackAndSlash/Components/Input/CombatInputComponent.h"
#include "HackAndSlash/CombatGameplayTags.h"
#include "HackAndSlash/AbilitySystem/CombatAbilitySystemComponent.h" //include our ability system component
#include "HackAndSlash/DataAssets/StartupData/DataAsset_HeroStartUpData.h"
#include "HackAndSlash/Components/Combat/HeroCombatComponent.h"
#include "HackAndSlash/Components/Input/CombatInputComponent.h"
#include "HackAndSlash/CombatDebugHelper.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "HackAndSlash/Components/UI/PlayerUIComponent.h"

struct FInputActionValue;


ACombatHeroCharacter::ACombatHeroCharacter()
{
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));
}

UPawnCombatComponent* ACombatHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* ACombatHeroCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* ACombatHeroCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void ACombatHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(!CharacterStartUpDataBase.IsNull()) //check if we have assigned a valid data asset to our soft reference
	{
		if(UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpDataBase.LoadSynchronous()) //we validate our load call
		{
			LoadedData->GiveToAbilitySystemComponent(CombatAbilitySystemComponent);
		}
	}
}

void ACombatHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))

	//We create a ref to our combat component
	UCombatInputComponent* CombatInputComponent = CastChecked<UCombatInputComponent>(PlayerInputComponent);

	//We call the Bind function from our CombatInputComponent and pass down its inputs
	CombatInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	//													Data asset		Actor performing		Pressed callback					released callback

	CombatInputComponent->BindNativeInputAction(InputConfigDataAsset,
		CombatGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this,
		&ThisClass::Input_SwitchTargetTriggered);

	CombatInputComponent->BindNativeInputAction(InputConfigDataAsset,
		CombatGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this,
		&ThisClass::Input_SwitchTargetCompleted);
	
}

void ACombatHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	CombatAbilitySystemComponent->OnAbilityInputPressed(InInputTag); 
}

void ACombatHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	CombatAbilitySystemComponent->OnAbilityInputReleased(InInputTag); 
}

void ACombatHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	MovementInputDirection = InputActionValue.Get<FVector2D>();
}

void ACombatHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this, //actor to send the event to
		MovementInputDirection.X>0.f?CombatGameplayTags::Player_Event_SwitchTarget_Right : CombatGameplayTags::Player_Event_SwitchTarget_Left, //event to send
		Data // gameplay event data
	);

	Debug::Print(TEXT("SwitchDirection: ") + MovementInputDirection.ToString(), FColor::Orange);
}

