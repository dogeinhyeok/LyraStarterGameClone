// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LyraPlayerState.generated.h"

class ULyraPawnData;
class ULyraExperienceDefinition;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ALyraPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() final;

	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);

	UPROPERTY()
	TObjectPtr<const ULyraPawnData> PawnData;
};
