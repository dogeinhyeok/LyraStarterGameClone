// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraInventoryManagerComponent.h"
#include "Logging/LogVerbosity.h"
#include "LyraInventoryItemDefinition.h"
#include "LyraInventoryItemInstance.h"
#include "GameFramework/Actor.h"
#include "../LogChannels.h"

ULyraInventoryItemInstance* FLyraInventoryList::AddEntry(
	TSubclassOf<ULyraInventoryItemDefinition> ItemDefinition)
{
	ULyraInventoryItemInstance* Result = nullptr;
	check(ItemDefinition);
	check(OwnerComponent);

	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	FLyraInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<ULyraInventoryItemInstance>(OwningActor);
	NewEntry.Instance->ItemDefinition = ItemDefinition;

	Result = NewEntry.Instance;
	return Result;
}

ULyraInventoryManagerComponent::ULyraInventoryManagerComponent(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), InventoryList(this)
{
}

ULyraInventoryItemInstance* ULyraInventoryManagerComponent::AddItemDefinition(
	TSubclassOf<ULyraInventoryItemDefinition> ItemDefinition)
{
	ULyraInventoryItemInstance* Result = nullptr;
	if (ItemDefinition)
	{
		Result = InventoryList.AddEntry(ItemDefinition);
	}

	return Result;
}