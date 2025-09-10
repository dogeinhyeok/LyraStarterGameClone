// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LyraGameModeBase.generated.h"

class ULyraExperienceDefinition;
class ULyraPawnData;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ALyraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALyraGameModeBase();

	virtual void InitGame(
		const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() final;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) final;

	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(
		AController* NewPlayer, const FTransform& SpawnTransform) final;

	void HandleMatchAssignmentIfNotExpectingOne();
	void OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId);
	bool IsExperienceLoaded() const;
	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
	const ULyraPawnData* GetPawnDataForController(AController* InController) const;
};
