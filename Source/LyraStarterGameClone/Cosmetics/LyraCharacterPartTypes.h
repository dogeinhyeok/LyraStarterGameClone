// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LyraCharacterPartTypes.generated.h"

USTRUCT(BlueprintType)
struct FLyraCharacterPartHandle
{
	GENERATED_BODY()

	void Reset() { PartHandle = INDEX_NONE; }

	bool IsValid() const { return PartHandle != INDEX_NONE; }

	UPROPERTY()
	int32 PartHandle = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct FLyraCharacterPart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> PartClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SocketName;
};