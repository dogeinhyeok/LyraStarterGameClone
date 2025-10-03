// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraEquipmentManagerComponent.h"
#include "AbilitySystemComponent.h"
#include "LyraEquipmentDefinition.h"
#include "LyraEquipmentInstance.h"
#include "../AbilitySystem/LyraAbilitySystemComponent.h"
#include "LyraStarterGameClone/AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

ULyraEquipmentInstance* FLyraEquipmentList::AddEntry(
	TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition)
{
	ULyraEquipmentInstance* Result = nullptr;
	check(EquipmentDefinition != nullptr);
	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());

	const ULyraEquipmentDefinition* EquipmentCDO =
		GetDefault<ULyraEquipmentDefinition>(EquipmentDefinition);

	TSubclassOf<ULyraEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;
	if (!InstanceType)
	{
		InstanceType = ULyraEquipmentInstance::StaticClass();
	}

	FLyraAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.EquipmentDefinition = EquipmentDefinition;
	NewEntry.Instance = NewObject<ULyraEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType);
	Result = NewEntry.Instance;

	ULyraAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	check(AbilitySystemComponent);
	{
		for (TObjectPtr<ULyraAbilitySet> AbilitySet : EquipmentCDO->AbilitySetsToGrant)
		{
			AbilitySet->GiveToAbilitySystem(
				AbilitySystemComponent, &NewEntry.GrantedHandles, Result);
		}
	}

	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);

	return Result;
}

void FLyraEquipmentList::RemoveEntry(ULyraEquipmentInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FLyraAppliedEquipmentEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			ULyraAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
			check(AbilitySystemComponent);
			{
				Entry.GrantedHandles.TakeFromAbilitySystem(AbilitySystemComponent);
			}
			Instance->DestroyEquipmentActors();
			EntryIt.RemoveCurrent();
		}
	}
}

ULyraAbilitySystemComponent* FLyraEquipmentList::GetAbilitySystemComponent() const
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();

	return Cast<ULyraAbilitySystemComponent>(
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor));
}

ULyraEquipmentManagerComponent::ULyraEquipmentManagerComponent(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), EquipmentList(this)
{
}

ULyraEquipmentInstance* ULyraEquipmentManagerComponent::EquipItem(
	TSubclassOf<ULyraEquipmentDefinition> EquipmentDefinition)
{
	ULyraEquipmentInstance* Result = nullptr;
	if (EquipmentDefinition)
	{
		Result = EquipmentList.AddEntry(EquipmentDefinition);

		if (Result)
		{
			Result->OnEquipped();
		}
	}
	return Result;
}

void ULyraEquipmentManagerComponent::UnequipItem(ULyraEquipmentInstance* ItemInstance)
{
	if (ItemInstance)
	{
		ItemInstance->OnUnequipped();

		EquipmentList.RemoveEntry(ItemInstance);
	}
}