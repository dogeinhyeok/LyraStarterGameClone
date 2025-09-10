// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraGameModeBase.h"
#include "LyraExperienceManagerComponent.h"
#include "LyraGameState.h"
#include "LyraExperienceDefinition.h"
#include "../LogChannels.h"
#include "../Player/LyraPlayerController.h"
#include "../Player/LyraPlayerState.h"
#include "../Character/LyraCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

ALyraGameModeBase::ALyraGameModeBase()
{
	GameStateClass = ALyraGameState::StaticClass();
	PlayerControllerClass = ALyraPlayerController::StaticClass();
	PlayerStateClass = ALyraPlayerState::StaticClass();
	DefaultPawnClass = ALyraCharacter::StaticClass();
}

void ALyraGameModeBase::InitGame(
	const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ALyraGameModeBase::InitGameState()
{
	Super::InitGameState();

	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(
		FLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ALyraGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

APawn* ALyraGameModeBase::SpawnDefaultPawnAtTransform_Implementation(
	AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(LogLyra, Log, TEXT("HandleStartingNewPlayer_Implementation is called"));
	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void ALyraGameModeBase::HandleMatchAssignmentIfNotExpectingOne() {}

bool ALyraGameModeBase::IsExperienceLoaded() const
{
	check(GameState);
	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	return ExperienceManagerComponent->IsExperienceLoaded();
}

void ALyraGameModeBase::OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience) {}
