// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraGameModeBase.h"
#include "LyraGameState.h"
#include "../Player/LyraPlayerController.h"
#include "../Player/LyraPlayerState.h"
#include "../Character/LyraCharacter.h"

ALyraGameModeBase::ALyraGameModeBase()
{
	GameStateClass = ALyraGameState::StaticClass();
	PlayerControllerClass = ALyraPlayerController::StaticClass();
	PlayerStateClass = ALyraPlayerState::StaticClass();
	DefaultPawnClass = ALyraCharacter::StaticClass();
}
