// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LyraInventoryItemDefinition.h"
#include "Templates/SubclassOf.h"
#include "LyraInventoryFragment_EquippableItem.generated.h"

/** forward declaration */
class ULyraEquipmentDefinition;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraInventoryFragment_EquippableItem :
	public ULyraInventoryItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Lyra")
	TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition;
};
