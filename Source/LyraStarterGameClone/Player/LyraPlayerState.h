// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LyraPlayerState.generated.h"

class ULyraPawnData;
class ULyraExperienceDefinition;

/**
 * 플레이어 상태: Experience 로딩 시 PawnData를 받아서 저장하고 관리하는 클래스
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ALyraPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void PostInitializeComponents() final;

	template <class T> const T* GetPawnData() const { return Cast<T>(PawnData); }
	void OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience);
	void SetPawnData(const ULyraPawnData* InPawnData);

	UPROPERTY()
	TObjectPtr<const ULyraPawnData> PawnData;
};
