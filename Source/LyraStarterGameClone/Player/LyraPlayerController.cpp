// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraPlayerController.cpp - 플레이어 컨트롤러 구현
 * 기본 APlayerController를 상속받는 빈 클래스 (추후 확장 예정)
 */

#include "LyraPlayerController.h"
#include "../AbilitySystem/LyraAbilitySystemComponent.h"
#include "../Camera/LyraPlayerCameraManager.h"
#include "../Player/LyraPlayerState.h"

ALyraPlayerController::ALyraPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ALyraPlayerCameraManager::StaticClass();
}

void ALyraPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (ULyraAbilitySystemComponent* LyraAbilitySystemComponent = GetLyraAbilitySystemComponent())
	{
		LyraAbilitySystemComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

ALyraPlayerState* ALyraPlayerController::GetLyraPlayerState() const
{
	return CastChecked<ALyraPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

ULyraAbilitySystemComponent* ALyraPlayerController::GetLyraAbilitySystemComponent() const
{
	const ALyraPlayerState* LyraPlayerState = GetLyraPlayerState();
	return (LyraPlayerState ? LyraPlayerState->GetLyraAbilitySystemComponent() : nullptr);
}