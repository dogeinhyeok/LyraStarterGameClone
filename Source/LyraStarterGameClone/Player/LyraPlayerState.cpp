// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraPlayerState.h"
#include "../GameModes/LyraPawnData.h"
#include "../GameModes/LyraExperienceDefinition.h"
#include "../GameModes/LyraExperienceManagerComponent.h"
#include "../GameModes/LyraGameModeBase.h"
#include "GameFramework/GameStateBase.h"

void ALyraPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(
		FLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ALyraPlayerState::OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience)
{
	if (ALyraGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ALyraGameModeBase>())
	{
		const ULyraPawnData* NewPawnData =
			GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

void ALyraPlayerState::SetPawnData(const ULyraPawnData* InPawnData)
{
	check(InPawnData);

	check(!PawnData);
	PawnData = InPawnData;
}
