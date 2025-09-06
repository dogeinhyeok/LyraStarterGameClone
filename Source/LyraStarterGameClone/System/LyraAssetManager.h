// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static ULyraAssetManager& Get();

	virtual void StartInitialLoading() final;

	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	void AddLoadedAsset(const UObject* Asset);

	UPROPERTY()
	TSet<TSoftObjectPtr<UObject>> LoadedAssets;

	FCriticalSection SyncObject;
};

template <typename AssetType>
AssetType* ULyraAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory)
{
	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();
		ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset : [%s]"), *AssetPath.ToString());
	}
	if (LoadedAsset && bkeepInMemory)
	{
		Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
	}
	return LoadedAsset;
}

template <typename AssetType>
TSubclassOf<AssetType> ULyraAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bkeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass = nullptr;
	const FSoftObjectPath  AssetPath = AssetPointer.ToSoftObjectPath();
	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load subclass : [%s]"), *AssetPath.ToString());
		}
	}
	if (LoadedSubclass && bkeepInMemory)
	{
		Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
	}
	return LoadedSubclass;
}
