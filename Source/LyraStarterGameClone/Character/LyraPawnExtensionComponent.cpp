// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "../LogChannels.h"
#include "../LyraGameplayTags.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Misc/CoreMiscDefines.h"

const FName ULyraPawnExtensionComponent::NAME_ActorFeatureName = TEXT("PawnExtension");

ULyraPawnExtensionComponent::ULyraPawnExtensionComponent(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

UE_DISABLE_OPTIMIZATION
void ULyraPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(LogLyra, Error,
				TEXT(
					"This component has been added to a Blueprint whose base class is not a Pawn!"));
			return;
		}
	}

	RegisterInitStateFeature();

	UGameFrameworkComponentManager* Manager =
		UGameFrameworkComponentManager::GetForActor(GetOwningActor());
}
UE_ENABLE_OPTIMIZATION

void ULyraPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

	ensure(TryToChangeInitState(FLyraGameplayTags::Get().InitState_Spawned));

	CheckDefaultInitialization();
}

void ULyraPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void ULyraPawnExtensionComponent::OnActorInitStateChanged(
	const FActorInitStateChangedParams& Params)
{
	IGameFrameworkInitStateInterface::OnActorInitStateChanged(Params);
}

bool ULyraPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager,
	FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	return IGameFrameworkInitStateInterface::CanChangeInitState(
		Manager, CurrentState, DesiredState);
}

void ULyraPawnExtensionComponent::CheckDefaultInitialization()
{
	IGameFrameworkInitStateInterface::CheckDefaultInitialization();
}