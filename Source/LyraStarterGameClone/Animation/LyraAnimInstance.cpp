// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraAnimInstance.h"
#include "AbilitySystemGlobals.h"

void ULyraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* AbilitySystemComponent =
				UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeWithAbilitySystem(AbilitySystemComponent);
		}
	}
}

void ULyraAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent)
{
	GameplayTagPropertyMap.Initialize(this, AbilitySystemComponent);
}
