// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "LyraCameraMode.generated.h"

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraCameraMode : public UObject
{
	GENERATED_BODY()

public:
	ULyraCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

UCLASS()
class ULyraCameraModeStack : public UObject
{
	GENERATED_BODY()

public:
	ULyraCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	TArray<TObjectPtr<ULyraCameraMode>> CameraModeInstances;

	UPROPERTY()
	TArray<TObjectPtr<ULyraCameraMode>> CameraModeStack;
};
