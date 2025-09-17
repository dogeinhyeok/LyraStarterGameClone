// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraGameplayTags.h"
#include "LogChannels.h"
#include "GameplayTagsManager.h"

FLyraGameplayTags FLyraGameplayTags::GameplayTags;

const FLyraGameplayTags& FLyraGameplayTags::Get()
{
	/*
	 * 첫 번쨰 실행: LyraAssetManager::StartInitialLoading()에서 InitializeNativeTags() 호출 전에
	 *   Pawn 스폰 시 TryToChangeInitState()가 호출되어 태그가 유효하지 않은 상태로 실패
	 * 두 번째 실행: 태그가 이미 메모리에 캐시되어 정상 작동
	 */
	if (!GameplayTags.InitState_Spawned.IsValid())
	{
		// Get() 호출 시 태그가 유효하지 않으면 자동으로 초기화하여 일관된 동작 보장
		InitializeNativeTags();
	}
	return GameplayTags;
}

void FLyraGameplayTags::InitializeNativeTags()
{
	UE_LOG(LogLyra, Warning, TEXT("InitializeNativeTags called"));
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	GameplayTags.AddAllTags(Manager);
	UE_LOG(LogLyra, Warning, TEXT("InitializeNativeTags completed"));
}

void FLyraGameplayTags::AddTag(
	FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	UE_LOG(LogLyra, Warning, TEXT("AddTag called for: %s"), ANSI_TO_TCHAR(TagName));
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
	UE_LOG(LogLyra, Warning, TEXT("AddTag result: %s"), *OutTag.ToString());
}

void FLyraGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	UE_LOG(LogLyra, Warning, TEXT("AddAllTags called"));
	AddTag(GameplayTags.InitState_Spawned, "InitState.Spawned",
		"1: Actor/Component has initially spawned and can be extended");
	AddTag(GameplayTags.InitState_DataAvailable, "InitState.DataAvailable",
		"2: All required data has been loaded/replicated and is ready for initialization");
	AddTag(GameplayTags.InitState_DataInitialized, "InitState.DataInitialized",
		"3: The available data has been initialized for this actor/component, but it is not ready for full gameplay");
	AddTag(GameplayTags.InitState_GameplayReady, "InitState.GameplayReady",
		"4: The actor/component is fully ready for active gameplay");

	AddTag(GameplayTags.InputTag_Move, "InputTag.Move", "1: Actor/Component is moving");
	AddTag(GameplayTags.InputTag_Look_Mouse, "InputTag.Look.Mouse",
		"2: Actor/Component is looking with mouse");

	UE_LOG(LogLyra, Warning, TEXT("InputTag_Move after AddTag: %s"),
		*GameplayTags.InputTag_Move.ToString());
	UE_LOG(LogLyra, Warning, TEXT("InputTag_Look_Mouse after AddTag: %s"),
		*GameplayTags.InputTag_Look_Mouse.ToString());
}
