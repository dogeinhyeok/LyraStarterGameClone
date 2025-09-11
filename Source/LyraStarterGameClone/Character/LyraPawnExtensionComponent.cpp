// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "../LogChannels.h"

ULyraPawnExtensionComponent::ULyraPawnExtensionComponent(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void ULyraPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(LogLyra, Error,
				TEXT(
					"This component has been added to a Blueprint whose base class is not a Pawn!"));
			return;
		}
	}

	RegisterInitStateFeature();

	UGameFrameworkComponentManager* Manager =
		UGameFrameworkComponentManager::GetForActor(GetOwningActor());
}

void ULyraPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULyraPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
