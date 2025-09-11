// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LyraGameState.generated.h"

class ULyraExperienceManagerComponent;

/**
 * 게임 상태: ExperienceManagerComponent를 포함하는 게임 상태 클래스
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ALyraGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALyraGameState();

public:
	UPROPERTY()
	TObjectPtr<ULyraExperienceManagerComponent> LyraExperienceManagerComponent;
};
