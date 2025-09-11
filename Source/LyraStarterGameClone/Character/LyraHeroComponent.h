// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "LyraHeroComponent.generated.h"

/**
 *
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class LYRASTARTERGAMECLONE_API ULyraHeroComponent :
	public UPawnComponent,
	public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	ULyraHeroComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
