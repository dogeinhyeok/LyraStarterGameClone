// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraAbilitySet.h"
#include "LyraAbilitySystemComponent.h"
#include "Abilities/LyraGameplayAbility.h"

void FLyraAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FLyraAbilitySet_GrantedHandles::TakeFromAbilitySystem(
	ULyraAbilitySystemComponent* LyraAbilitySystemComponent)
{
	if (!LyraAbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			LyraAbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

ULyraAbilitySet::ULyraAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULyraAbilitySet::GiveToAbilitySystem(ULyraAbilitySystemComponent* LyraAbilitySystemComponent,
	FLyraAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject)
{
	check(LyraAbilitySystemComponent);

	if (!LyraAbilitySystemComponent->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); AbilityIndex++)
	{
		const FLyraAbilitySet_GameplayAbility& AbilityToGrant =
			GrantedGameplayAbilities[AbilityIndex];
		if (!IsValid(AbilityToGrant.Ability))
		{
			continue;
		}

		ULyraGameplayAbility* AbilityCDO =
			AbilityToGrant.Ability->GetDefaultObject<ULyraGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle =
			LyraAbilitySystemComponent->GiveAbility(AbilitySpec);
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}