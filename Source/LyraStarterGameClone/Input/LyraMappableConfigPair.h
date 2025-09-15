// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMappableInputConfig.h"
#include "LyraMappableConfigPair.generated.h"

USTRUCT()
struct FLyraMappableConfigPair
{
	GENERATED_BODY()

public:
	FLyraMappableConfigPair() = default;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	UPROPERTY(EditAnywhere)
	bool bShouldActivateAutomatically = true;
};
