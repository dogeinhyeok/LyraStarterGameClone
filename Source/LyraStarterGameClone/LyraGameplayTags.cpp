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
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	GameplayTags.AddAllTags(&Manager);
}

void FLyraGameplayTags::AddTag(
	FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName(TagName), FString(TEXT("(Native) %s")) + FString(TagComment));
}

void FLyraGameplayTags::AddAllTags(UGameplayTagsManager* Manager)
{
	AddTag(InitState_Spawned, "InitState.Spawned",
		"1: Actor/Component has initially spawned and can be extended");
	AddTag(InitState_DataAvailable, "InitState.DataAvailable",
		"2: All required data has been loaded/replicated and is ready for initialization");
	AddTag(InitState_DataInitialized, "InitState.DataInitialized",
		"3: The available data has been initialized for this actor/component, but it is not ready for full gameplay");
	AddTag(InitState_GameplayReady, "InitState.GameplayReady",
		"4: The actor/component is fully ready for active gameplay");
}
