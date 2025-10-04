// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapons/LyraWeaponInstance.h"
#include "LyraRangedWeaponInstance.generated.h"

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraRangedWeaponInstance : public ULyraWeaponInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(
		EditAnywhere, BlueprintReadOnly, Category = "WeaponConfig", meta = (ForceUnits = "cm"))
	float MaxDamageRange = 25000.0f;

	UPROPERTY(
		EditAnywhere, BlueprintReadOnly, Category = "WeaponConfig", meta = (ForceUnits = "cm"))
	float BulletTraceWeaponRadius = 0.0f;
};
