// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/ObjectMacros.h"
#include "LyraInventoryManagerComponent.generated.h"

class ULyraInventoryItemInstance;
class ULyraInventoryItemDefinition;

USTRUCT(BlueprintType)
struct FLyraInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ULyraInventoryItemInstance> Instance = nullptr;
};

USTRUCT(BlueprintType)
struct FLyraInventoryList
{
	GENERATED_BODY()

	FLyraInventoryList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{
	}

	UPROPERTY()
	TArray<FLyraInventoryEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LYRASTARTERGAMECLONE_API ULyraInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	ULyraInventoryManagerComponent(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	FLyraInventoryList InventoryList;
};
