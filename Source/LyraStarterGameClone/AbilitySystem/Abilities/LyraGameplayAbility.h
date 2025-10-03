// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LyraGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ELyraAbilityActivationPolicy : uint8
{
	OnInputTriggered,
	WhileInputActive,
	OnSpawn,
};

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULyraGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|AbilityActivation")
	ELyraAbilityActivationPolicy ActivationPolicy;
};
