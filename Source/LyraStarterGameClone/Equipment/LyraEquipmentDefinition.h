// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LyraEquipmentDefinition.generated.h"

class ULyraEquipmentInstance;

USTRUCT(BlueprintType)
struct FLyraEquipmentActorToSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform AttachTransform;
};

/**
 *
 */
UCLASS(Blueprintable)
class LYRASTARTERGAMECLONE_API ULyraEquipmentDefinition : public UObject
{
	GENERATED_BODY()

public:
	ULyraEquipmentDefinition(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<ULyraEquipmentInstance> InstanceType;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TArray<FLyraEquipmentActorToSpawn> ActorToSpawn;
};
