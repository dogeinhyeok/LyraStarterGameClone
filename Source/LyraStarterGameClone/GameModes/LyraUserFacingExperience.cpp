// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraUserFacingExperience.cpp - 사용자 친화적 Experience 데이터 에셋 구현
 * 맵과 Experience를 연결하는 사용자 친화적인 데이터 에셋 (현재는 빈 구현)
 */

#include "LyraUserFacingExperience.h"
#include "CommonSessionSubsystem.h"

UCommonSession_HostSessionRequest* ULyraUserFacingExperience::CreateHostingRequest() const
{
	const FString ExperienceName = ExperienceID.PrimaryAssetName.ToString();

	UCommonSession_HostSessionRequest* Result = NewObject<UCommonSession_HostSessionRequest>();
	Result->MapID = MapID;
	Result->ExtraArgs.Add(FString("Experience"), ExperienceName);

	return Result;
}
