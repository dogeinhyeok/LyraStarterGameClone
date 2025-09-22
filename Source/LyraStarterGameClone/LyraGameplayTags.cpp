// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraGameplayTags.h"
#include "LogChannels.h"
#include "GameplayTagsManager.h"

FLyraGameplayTags FLyraGameplayTags::GameplayTags;

void FLyraGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	GameplayTags.AddAllTags(Manager);
}

void FLyraGameplayTags::AddTag(
	FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	// 먼저 기존 태그가 있는지 확인
	OutTag = UGameplayTagsManager::Get().RequestGameplayTag(FName(TagName), false);

	// 태그가 없으면 Native Tag로 추가 시도
	if (!OutTag.IsValid())
	{
		OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
	}
}

void FLyraGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
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
}
