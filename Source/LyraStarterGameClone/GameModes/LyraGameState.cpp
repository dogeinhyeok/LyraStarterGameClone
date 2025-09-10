// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraGameState.h"
#include "LyraExperienceManagerComponent.h"

ALyraGameState::ALyraGameState()
{
	LyraExperienceManagerComponent = CreateDefaultSubobject<ULyraExperienceManagerComponent>(
		TEXT("LyraExperienceManagerComponent"));
}