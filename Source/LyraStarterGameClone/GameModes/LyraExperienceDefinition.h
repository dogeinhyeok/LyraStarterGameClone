// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraExperienceDefinition.generated.h"

class ULyraPawnData;

/**
 * Experience 정의: 게임 경험을 정의하는 데이터 에셋 (DefaultPawnData와 GameFeatures 포함)
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TObjectPtr<ULyraPawnData> DefaultPawnData;

	/*
	 * 게임 기능을 활성화할 때 사용되는 문자열 배열
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TArray<FString> GameFeaturesToEnable;
};
