// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraInventoryItemInstance.h"
#include "LyraInventoryItemDefinition.h"

ULyraInventoryItemInstance::ULyraInventoryItemInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const ULyraInventoryItemFragment* ULyraInventoryItemInstance::FindFragmentByClass(
	TSubclassOf<ULyraInventoryItemFragment> FragmentClass) const
{
	if ((ItemDefinition != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<ULyraInventoryItemDefinition>(ItemDefinition)
			->FindFragmentByClass(FragmentClass);
	}
	return nullptr;
}