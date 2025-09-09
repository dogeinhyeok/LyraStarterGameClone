// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "LyraExperienceManagerComponent.generated.h"

class ULyraExperienceDefinition;

enum class ELyraExperienceLoadState : uint8
{
	Unloaded,
	Loading,
	Loaded,
	Deactivated,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FLyraExperienceLoaded, const ULyraExperienceDefinition*);

/**
 * 
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()

public:
	bool IsExperienceLoaded() { return (LoadState == ELyraExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }

	void CallOrRegister_OnExperienceLoaded(FLyraExperienceLoaded::FDelegate&& Delegate);

public:
	UPROPERTY()
	TObjectPtr<ULyraExperienceDefinition> CurrentExperience;

	ELyraExperienceLoadState LoadState = ELyraExperienceLoadState::Unloaded;

	FLyraExperienceLoaded OnExperienceLoaded;
};
