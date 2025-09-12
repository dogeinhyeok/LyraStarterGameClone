// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "../LogChannels.h"
#include "../LyraGameplayTags.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "LyraPawnData.h"

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

void ULyraPawnExtensionComponent::SetPawnData(const ULyraPawnData* InPawnData)
{
	APawn* Pawn = GetPawnChecked<APawn>();
	if (Pawn->GetLocalRole() == ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		return;
	}

	PawnData = InPawnData;
}

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
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();
		if (Params.FeatureState == InitTags.InitState_GameplayReady)
		{
			CheckDefaultInitialization();
		}
	}
}

bool ULyraPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager,
	FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	if (!CurrentState.IsValid() && DesiredState == InitTags.InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}

	if (CurrentState == InitTags.InitState_Spawned
		&& DesiredState == InitTags.InitState_DataAvailable)
	{
		if (Pawn)
		{
			return false;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		if (bIsLocallyControlled)
		{
			if (!GetController<AController>())
			{
				return false;
			}
		}

		return true;
	}

	if (CurrentState == InitTags.InitState_DataAvailable
		&& DesiredState == InitTags.InitState_DataInitialized)
	{
		return Manager->HaveAllFeaturesReachedInitState(Pawn, InitTags.InitState_DataAvailable);
	}

	if (CurrentState == InitTags.InitState_DataInitialized
		&& DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void ULyraPawnExtensionComponent::CheckDefaultInitialization()
{
	CheckDefaultInitializationForImplementers();

	const FLyraGameplayTags& InitTags = FLyraGameplayTags::Get();

	static const TArray<FGameplayTag> StateChain = { InitTags.InitState_Spawned,
		InitTags.InitState_DataAvailable, InitTags.InitState_DataInitialized,
		InitTags.InitState_GameplayReady };

	ContinueInitStateChain(StateChain);
}