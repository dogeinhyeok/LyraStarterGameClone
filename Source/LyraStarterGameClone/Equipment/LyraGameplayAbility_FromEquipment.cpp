// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraGameplayAbility_FromEquipment.h"
#include "LyraEquipmentInstance.h"

ULyraEquipmentInstance* ULyraGameplayAbility_FromEquipment::GetAssociatedEquipment() const
{
	if (FGameplayAbilitySpec* Spec = UGameplayAbility::GetCurrentAbilitySpec())
	{
		return Cast<ULyraEquipmentInstance>(Spec->SourceObject.Get());
	}
	return nullptr;
}