// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraCameraComponent.h"
#include "LyraCameraMode.h"

ULyraCameraComponent::ULyraCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULyraCameraComponent::OnRegister()
{
	Super::OnRegister();
	if (!CameraModeStack)
	{
		CameraModeStack = NewObject<ULyraCameraModeStack>(this);
	}
}

void ULyraCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	check(CameraModeStack);

	UpdateCameraModes();
}

void ULyraCameraComponent::UpdateCameraModes()
{
	check(CameraModeStack);

	if (DetermineCameraModeDelegate.IsBound())
	{
		if (const TSubclassOf<ULyraCameraMode> CameraMode = DetermineCameraModeDelegate.Execute())
		{
		}
	}
}