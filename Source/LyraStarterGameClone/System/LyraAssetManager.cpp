// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraAssetManager.h"
#include "LyraStarterGameClone/LogChannels.h"

ULyraAssetManager& ULyraAssetManager::Get()
{
	check(GEngine)

	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogLyra, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be LyraAssetManager!"));

	return *NewObject<ULyraAssetManager>();
}

bool ULyraAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return true;
}

UE_DISABLE_OPTIMIZATION
void ULyraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
UE_ENABLE_OPTIMIZATION

UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsAsset())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("SynchronousLoadAsset [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}
		if (UAssetManager::IsInitialized())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}
		return AssetPath.TryLoad();
	}
	return nullptr;
}

void ULyraAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(const_cast<UObject*>(Asset));
	}
}