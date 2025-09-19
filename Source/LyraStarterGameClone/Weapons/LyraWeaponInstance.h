// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Cosmetics/LyraCosmeticAnimationTypes.h"
#include "../Equipment/LyraEquipmentInstance.h"
#include "LyraWeaponInstance.generated.h"

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraWeaponInstance : public ULyraEquipmentInstance
{
	GENERATED_BODY()

public:
	ULyraWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	FLyraAnimLayerSelectionSet EquippedAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	FLyraAnimLayerSelectionSet UnequippedAnimSet;
};
