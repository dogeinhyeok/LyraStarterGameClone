// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LyraExperienceDefinition.generated.h"

class LyraPawnData;

/**
 * 
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TObjectPtr<LyraPawnData> DefaultPawnData;

	/*
	 * 게임 기능을 활성화할 때 사용되는 문자열 배열
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	TArray<FString> GameFeaturesToEnable;
};
