// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LyraPlayerState.generated.h"

class ULyraPawnData;
class ULyraExperienceDefinition;

/**
 *
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
	const ULyraPawnData* GetPawnDataForController(AController* InController) const;

	UPROPERTY()
	TObjectPtr<const ULyraPawnData> PawnData;
};
