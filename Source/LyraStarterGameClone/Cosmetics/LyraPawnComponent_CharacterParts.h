// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraCharacterPartTypes.h"
#include "LyraCosmeticAnimationTypes.h"
#include "Components/PawnComponent.h"
#include "LyraPawnComponent_CharacterParts.generated.h"

class ULyraPawnComponent_CharacterParts;

USTRUCT()
struct FLyraAppliedCharacterPartEntry
{
	GENERATED_BODY()

	UPROPERTY()
	FLyraCharacterPart Part;

	UPROPERTY()
	int32 PartHandle = INDEX_NONE;

	UPROPERTY()
	TObjectPtr<UChildActorComponent> SpawnedComponent = nullptr;
};

USTRUCT(BlueprintType)
struct FLyraCharacterPartList
{
	GENERATED_BODY()

	FLyraCharacterPartList() : OwnerComponent(nullptr) {}

	FLyraCharacterPartList(ULyraPawnComponent_CharacterParts* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

	bool SpawnActorForEntry(FLyraAppliedCharacterPartEntry& Entry);
	void DestroyActorForEntry(FLyraAppliedCharacterPartEntry& Entry);

	FLyraCharacterPartHandle AddEntry(FLyraCharacterPart NewPart);
	void RemoveEntry(FLyraCharacterPartHandle Handle);

	FGameplayTagContainer CollectCombinedTags() const;

	UPROPERTY()
	TArray<FLyraAppliedCharacterPartEntry> Entries;

	UPROPERTY()
	TObjectPtr<ULyraPawnComponent_CharacterParts> OwnerComponent;

	int32 PartHandleCounter = 0;
};

UCLASS()
class LYRASTARTERGAMECLONE_API ULyraPawnComponent_CharacterParts : public UPawnComponent
{
	GENERATED_BODY()

public:
	ULyraPawnComponent_CharacterParts(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	USkeletalMeshComponent* GetParentMeshComponent() const;
	USceneComponent* GetSceneComponentToAttachTo() const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Cosmetics")
	FGameplayTagContainer GetCombinedTags(FGameplayTag RequiredPrefix) const;
	void BroadcastChanged();

	FLyraCharacterPartHandle AddCharacterPart(const FLyraCharacterPart& NewPart);
	void RemoveCharacterPart(FLyraCharacterPartHandle Handle);

	UPROPERTY()
	FLyraCharacterPartList CharacterPartList;

	UPROPERTY(EditAnywhere, Category = "Cosmetics")
	FLyraAnimBodyStyleSelectionSet BodyMeshes;
};
