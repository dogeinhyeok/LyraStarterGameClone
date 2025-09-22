// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "UObject/ObjectMacros.h"
#include "LyraEquipmentManagerComponent.generated.h"

class ULyraEquipmentDefinition;
class ULyraEquipmentInstance;

USTRUCT()
struct FLyraAppliedEquipmentEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<ULyraEquipmentInstance> EquipmentDefinition;

	UPROPERTY()
	TObjectPtr<ULyraEquipmentInstance> Instance = nullptr;
};

USTRUCT()
struct FLyraEquipmentList
{
	GENERATED_BODY()

	FLyraEquipmentList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{
	}

	UPROPERTY()
	TArray<FLyraAppliedEquipmentEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent = nullptr;
};

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	ULyraEquipmentManagerComponent(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	FLyraEquipmentList EquipmentList;
};
