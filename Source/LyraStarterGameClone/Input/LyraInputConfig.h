// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "LyraInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FLyraInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	ULyraInputConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const UInputAction* FindNativeInputActionForTag(
		const FGameplayTag& InputTag, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForTag(
		const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (TitleProperty = "InputActions"))
	TArray<FLyraInputAction> NativeInputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (TitleProperty = "InputActions"))
	TArray<FLyraInputAction> AbilityInputActions;
};
