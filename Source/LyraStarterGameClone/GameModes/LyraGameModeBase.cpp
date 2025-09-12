// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraGameModeBase.cpp - 메인 게임 모드 구현
 * Experience 로딩을 시작하고 완료 시 플레이어를 스폰하는 메인 게임 모드
 */

#include "LyraGameModeBase.h"
#include "LyraExperienceDefinition.h"
#include "LyraExperienceManagerComponent.h"
#include "LyraGameState.h"
#include "../Character/LyraPawnData.h"
#include "../Character/LyraCharacter.h"
#include "../LogChannels.h"
#include "../Player/LyraPlayerController.h"
#include "../Player/LyraPlayerState.h"
#include "Engine/World.h"
#include "LyraStarterGameClone/Character/LyraPawnExtensionComponent.h"
#include "Misc/CoreMiscDefines.h"
#include "TimerManager.h"
#include "UObject/PrimaryAssetId.h"

/**
 * ALyraGameModeBase 생성자 - 게임 모드의 기본 클래스들을 설정
 */
ALyraGameModeBase::ALyraGameModeBase()
{
	GameStateClass = ALyraGameState::StaticClass();
	PlayerControllerClass = ALyraPlayerController::StaticClass();
	PlayerStateClass = ALyraPlayerState::StaticClass();
	DefaultPawnClass = ALyraCharacter::StaticClass();
}

/**
 * InitGame - 게임 초기화 시 호출되는 함수
 */
void ALyraGameModeBase::InitGame(
	const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

/**
 * InitGameState - 게임 상태 초기화 및 Experience 델리게이트 등록
 */
void ALyraGameModeBase::InitGameState()
{
	Super::InitGameState();

	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(
		FOnLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

/**
 * GetDefaultPawnClassForController_Implementation - 컨트롤러에 대한 기본 Pawn 클래스 반환
 */
UClass* ALyraGameModeBase::GetDefaultPawnClassForController_Implementation(
	AController* InController)
{
	if (const ULyraPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

/**
 * HandleStartingNewPlayer_Implementation - 새 플레이어 시작 처리
 */
UE_DISABLE_OPTIMIZATION
void ALyraGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}
UE_ENABLE_OPTIMIZATION

/**
 * SpawnDefaultPawnAtTransform_Implementation - 지정된 위치에 기본 Pawn 스폰
 */
APawn* ALyraGameModeBase::SpawnDefaultPawnAtTransform_Implementation(
	AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	SpawnInfo.bDeferConstruction = true;

	if (UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer))
	{
		if (APawn* SpawnedPawn =
				GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo))
		{
			if (ULyraPawnExtensionComponent* PawnExtensionComponent =
					ULyraPawnExtensionComponent::FindPawnExtensionComponent(SpawnedPawn))
			{
				if (const ULyraPawnData* PawnData = GetPawnDataForController(NewPlayer))
				{
					PawnExtensionComponent->SetPawnData(PawnData);
				}
			}
			SpawnedPawn->FinishSpawning(SpawnTransform);
			return SpawnedPawn;
		}
	}

	return nullptr;
}

/**
 * HandleMatchAssignmentIfNotExpectingOne - 매치 할당이 없을 때 기본 Experience 설정
 */
void ALyraGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(
			FPrimaryAssetType("LyraExperienceDefinition"), FName("B_LyraDefaultExperience"));
	}

	OnMatchAssignmentGiven(ExperienceId);
}

/**
 * OnMatchAssignmentGiven - 매치 할당이 주어졌을 때 Experience 로딩 시작
 */
void ALyraGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	check(ExperienceId.IsValid());
	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	UE_LOG(LogLyra, Log, TEXT("HandleStartingNewPlayer_Implementation is called"));
	ExperienceManagerComponent->ServerSetCurrentExperience(ExperienceId);
}

/**
 * IsExperienceLoaded - Experience가 로딩되었는지 확인
 */
bool ALyraGameModeBase::IsExperienceLoaded() const
{
	check(GameState);
	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	return ExperienceManagerComponent->IsExperienceLoaded();
}

/**
 * OnExperienceLoaded - Experience 로딩 완료 시 플레이어 스폰 처리
 */
void ALyraGameModeBase::OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience)
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator();
		 Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Cast<APlayerController>(*Iterator);
		check(PlayerController);
		if (PlayerController && PlayerController->GetPawn() == nullptr)
		{
			if (PlayerCanRestart(PlayerController))
			{
				RestartPlayer(PlayerController);
			}
		}
	}
}

/**
 * GetPawnDataForController - 컨트롤러에 대한 Pawn 데이터 반환
 */
const ULyraPawnData* ALyraGameModeBase::GetPawnDataForController(AController* InController) const
{
	if (InController)
	{
		if (const ALyraPlayerState* LyraPlayerState =
				InController->GetPlayerState<ALyraPlayerState>())
		{
			if (const ULyraPawnData* PlayerPawnData = LyraPlayerState->GetPawnData<ULyraPawnData>())
			{
				return PlayerPawnData;
			}
		}
	}

	check(GameState);
	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	if (ExperienceManagerComponent->IsExperienceLoaded())
	{
		const ULyraExperienceDefinition* Experience =
			ExperienceManagerComponent->GetCurrentExperienceChecked();
		check(Experience);
		if (Experience->DefaultPawnData)
		{
			return Experience->DefaultPawnData;
		}
	}

	return nullptr;
}