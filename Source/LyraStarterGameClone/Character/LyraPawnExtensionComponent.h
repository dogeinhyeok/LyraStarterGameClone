// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "LyraPawnExtensionComponent.generated.h"

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraPawnExtensionComponent :
	public UPawnComponent,
	public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	ULyraPawnExtensionComponent(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final;
};
