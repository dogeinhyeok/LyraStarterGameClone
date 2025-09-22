// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "LyraQuickBarComponent.generated.h"

class ULyraInventoryItemInstance;
class ULyraEquipmentInstance;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraQuickBarComponent : public UControllerComponent
{
	GENERATED_BODY()

public:
	ULyraQuickBarComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	int32 NumSlots = 3;

	UPROPERTY()
	TArray<TSubclassOf<ULyraInventoryItemInstance>> Slots;

	UPROPERTY()
	int32 ActiveSlotIndex = -1;

	UPROPERTY()
	TObjectPtr<ULyraEquipmentInstance> EquippedItem;
};
