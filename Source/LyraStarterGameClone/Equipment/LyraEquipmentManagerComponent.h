// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "LyraStarterGameClone/AbilitySystem/LyraAbilitySystemComponent.h"
#include "UObject/ObjectMacros.h"
#include "../AbilitySystem/LyraAbilitySet.h"
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

	UPROPERTY()
	FLyraAbilitySet_GrantedHandles GrantedHandles;
};

USTRUCT()
struct FLyraEquipmentList
{
	GENERATED_BODY()

	FLyraEquipmentList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{
	}

	ULyraEquipmentInstance* AddEntry(TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(ULyraEquipmentInstance* ItemInstance);

	ULyraAbilitySystemComponent* GetAbilitySystemComponent() const;

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

	ULyraEquipmentInstance* EquipItem(TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition);
	void UnequipItem(ULyraEquipmentInstance* ItemInstance);

	UFUNCTION(BlueprintCallable)
	TArray<ULyraEquipmentInstance*> GetEquipmentInstancesOfType(
		TSubclassOf<ULyraEquipmentInstance> InstanceType) const;

	UPROPERTY()
	FLyraEquipmentList EquipmentList;
};
