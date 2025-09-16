// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraUserFacingExperience.generated.h"

class UCommonSession_HostSessionRequest;

/**
 * 사용자 경험: 맵과 Experience를 연결하는 사용자 친화적인 데이터 에셋
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraUserFacingExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure = false)
	UCommonSession_HostSessionRequest* CreateHostingRequest() const;

	UPROPERTY(
		BlueprintReadWrite, EditAnywhere, Category = "Experience", meta = (AllowedTypes = "Map"))
	FPrimaryAssetId MapID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Experience",
		meta = (AllowedTypes = "LyraExperienceDefinition"))
	FPrimaryAssetId ExperienceID;
};
