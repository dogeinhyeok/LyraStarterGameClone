// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraExperienceManagerComponent.h"
#include "LyraExperienceDefinition.h"

void ULyraExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(
	FLyraExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.ExecuteIfBound(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}