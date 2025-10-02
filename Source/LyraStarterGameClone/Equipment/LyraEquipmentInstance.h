// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LyraEquipmentInstance.generated.h"

struct FLyraEquipmentActorToSpawn;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraEquipmentInstance : public UObject
{
	GENERATED_BODY()

public:
	ULyraEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(
		BlueprintImplementableEvent, Category = "Equipment", meta = (DisplayName = "OnEquipped"))
	void K2_OnEquipped();

	UFUNCTION(
		BlueprintImplementableEvent, Category = "Equipment", meta = (DisplayName = "OnUnequipped"))
	void K2_OnUnequipped();

	UFUNCTION(BlueprintPure, Category = "Equipment")
	APawn* GetPawn() const;

	void SpawnEquipmentActors(const TArray<FLyraEquipmentActorToSpawn>& ActorsToSpawn);
	void DestroyEquipmentActors();

	UFUNCTION(BlueprintPure, Category = "Equipment", meta = (DeterminesOutputType = "PawnType"))
	APawn* GetTypedPawn(TSubclassOf<APawn> PawnType) const;

	virtual void OnEquipped();
	virtual void OnUnequipped();

	UPROPERTY()
	TObjectPtr<UObject> Instigator;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;
};
