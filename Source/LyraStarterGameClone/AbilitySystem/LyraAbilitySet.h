// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpec.h"
#include "LyraAbilitySet.generated.h"

class ULyraGameplayAbility;
class ULyraAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FLyraAbilitySet_GameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULyraGameplayAbility> Ability = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;
};

USTRUCT(BlueprintType)
struct FLyraAbilitySet_GrantedHandles
{
	GENERATED_BODY()

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void TakeFromAbilitySystem(ULyraAbilitySystemComponent* LyraAbilitySystemComponent);

protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
};

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	ULyraAbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void GiveToAbilitySystem(ULyraAbilitySystemComponent* LyraAbilitySystemComponent,
		FLyraAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr);

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<FLyraAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
