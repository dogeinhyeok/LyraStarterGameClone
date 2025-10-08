#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "LyraGameplayCueManager.generated.h"

UCLASS()
class ULyraGameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()

public:
	static ULyraGameplayCueManager* Get();

	ULyraGameplayCueManager(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void RefreshGameplayCuePrimaryAsset();
};