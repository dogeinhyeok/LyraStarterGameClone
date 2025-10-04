// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../AbilitySystem/Abilities/LyraGameplayAbility.h"
#include "LyraGameplayAbility_FromEquipment.generated.h"

class ULyraEquipmentInstance;

/**
 *
 */
UCLASS(Blueprintable)
class LYRASTARTERGAMECLONE_API ULyraGameplayAbility_FromEquipment : public ULyraGameplayAbility
{
	GENERATED_BODY()

public:
	ULyraEquipmentInstance* GetAssociatedEquipment() const;
};
