// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"
#include "UObject/NoExportTypes.h"
#include "UObject/UObjectGlobals.h"
#include "LyraInventoryItemDefinition.generated.h"

UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class ULyraInventoryItemFragment : public UObject
{
	GENERATED_BODY()

public:
};

/**
 *
 */
UCLASS(Blueprintable)
class LYRASTARTERGAMECLONE_API ULyraInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	ULyraInventoryItemDefinition(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	TArray<TObjectPtr<ULyraInventoryItemFragment>> Fragments;
};
