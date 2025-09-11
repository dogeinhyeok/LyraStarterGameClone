// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraGameState.cpp - 게임 상태 구현
 * ExperienceManagerComponent를 포함하는 게임 상태 클래스
 */

#include "LyraGameState.h"
#include "LyraExperienceManagerComponent.h"

/**
 * ALyraGameState 생성자 - ExperienceManagerComponent 생성 및 초기화
 */
ALyraGameState::ALyraGameState()
{
	LyraExperienceManagerComponent = CreateDefaultSubobject<ULyraExperienceManagerComponent>(
		TEXT("LyraExperienceManagerComponent"));
}