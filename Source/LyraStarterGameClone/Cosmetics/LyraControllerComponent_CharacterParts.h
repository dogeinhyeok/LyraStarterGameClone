// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraCharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "LyraControllerComponent_CharacterParts.generated.h"

class ULyraPawnComponent_CharacterParts;

USTRUCT()
struct FLyraControllerCharacterPartEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FLyraCharacterPart Part;

	FLyraCharacterPartHandle Handle;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class ULyraControllerComponent_CharacterParts : public UControllerComponent
{
	GENERATED_BODY()

public:
	ULyraControllerComponent_CharacterParts(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, Category = Cosmetics)
	TArray<FLyraControllerCharacterPartEntry> CharacterParts;
};