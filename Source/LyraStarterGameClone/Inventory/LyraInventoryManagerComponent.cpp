// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraInventoryManagerComponent.h"
#include "LyraInventoryItemDefinition.h"
#include "LyraInventoryItemInstance.h"

ULyraInventoryManagerComponent::ULyraInventoryManagerComponent(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;
}
