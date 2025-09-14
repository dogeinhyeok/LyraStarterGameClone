// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraCameraMode.h"
#include "Camera/CameraComponent.h"
#include "LyraCameraComponent.generated.h"

class ULyraCameraModeStack;

template <typename TClass> class TSubclassOf;

DECLARE_DELEGATE_RetVal(TSubclassOf<ULyraCameraMode>, FLyraCameraModeDelegate);

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	ULyraCameraComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static ULyraCameraComponent* FindCameraComponent(const AActor* Actor)
	{
		return (Actor) ? Actor->FindComponentByClass<ULyraCameraComponent>() : nullptr;
	};

	void UpdateCameraModes();

	virtual void OnRegister() final;
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) final;

	UPROPERTY()
	TObjectPtr<ULyraCameraModeStack> CameraModeStack;

	FLyraCameraModeDelegate DetermineCameraModeDelegate;
};
