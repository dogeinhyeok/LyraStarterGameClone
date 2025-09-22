// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraInventoryItemDefinition.h"
#include "Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "LyraInventoryItemInstance.generated.h"

class ULyraInventoryItemFragment;
class ULyraInventoryItemDefinition;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraInventoryItemInstance : public UObject
{
	GENERATED_BODY()

public:
	ULyraInventoryItemInstance(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const ULyraInventoryItemFragment* FindFragmentByClass(
		TSubclassOf<ULyraInventoryItemFragment> FragmentClass) const;

	template <typename ResultClass> const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}

	UPROPERTY()
	TSubclassOf<ULyraInventoryItemDefinition> ItemDefinition;
};
