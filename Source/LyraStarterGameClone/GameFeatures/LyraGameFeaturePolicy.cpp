#include "LyraGameFeaturePolicy.h"
#include "GameFeatureAction.h"
#include "GameFeatureAction_AddGameplayCuePath.h"
#include "GameFeatureData.h"
#include "GameplayCueSet.h"
#include "../AbilitySystem/LyraGameplayCueManager.h"

ULyraGameFeaturePolicy::ULyraGameFeaturePolicy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULyraGameFeaturePolicy::InitGameFeatureManager()
{
	Observers.Add(NewObject<ULyraGameFeature_AddGameplayCuePaths>());

	UGameFeaturesSubsystem& Subsystem = UGameFeaturesSubsystem::Get();
	for (UObject* Observer : Observers)
	{
		Subsystem.AddObserver(Observer);
	}

	Super::InitGameFeatureManager();
}

void ULyraGameFeaturePolicy::ShutdownGameFeatureManager()
{
	Super::ShutdownGameFeatureManager();

	UGameFeaturesSubsystem& Subsystem = UGameFeaturesSubsystem::Get();
	for (UObject* Observer : Observers)
	{
		Subsystem.RemoveObserver(Observer);
	}

	Observers.Empty();
}

void ULyraGameFeature_AddGameplayCuePaths::OnGameFeatureRegistering(
	const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)
{
	const FString PluginRootPath = TEXT("/") + PluginName;

	for (const UGameFeatureAction* Action : GameFeatureData->GetActions())
	{
		if (const UGameFeatureAction_AddGameplayCuePath* AddGameplayCueGFA =
				Cast<UGameFeatureAction_AddGameplayCuePath>(Action))
		{
			const TArray<FDirectoryPath>& DirsToAdd = AddGameplayCueGFA->DirectoryPathsToAdd;

			if (ULyraGameplayCueManager* GCM = ULyraGameplayCueManager::Get())
			{
				UGameplayCueSet* RuntimeGameplayCueSet = GCM->GetRuntimeCueSet();
				const int32 PreInitializeNumCues =
					RuntimeGameplayCueSet ? RuntimeGameplayCueSet->GameplayCueData.Num() : 0;

				for (const FDirectoryPath& Directory : DirsToAdd)
				{
					FString MutablePath = Directory.Path;

					UGameFeaturesSubsystem::FixPluginPackagePath(
						MutablePath, PluginRootPath, false);

					GCM->AddGameplayCueNotifyPath(MutablePath, false);
				}

				if (!DirsToAdd.IsEmpty())
				{
					GCM->InitializeRuntimeObjectLibrary();
				}

				const int32 PostInitializeNumCues =
					RuntimeGameplayCueSet ? RuntimeGameplayCueSet->GameplayCueData.Num() : 0;

				if (PostInitializeNumCues != PreInitializeNumCues)
				{
					GCM->RefreshGameplayCuePrimaryAsset();
				}
			}
		}
	}

	IGameFeatureStateChangeObserver::OnGameFeatureRegistering(
		GameFeatureData, PluginName, PluginURL);
}

void ULyraGameFeature_AddGameplayCuePaths::OnGameFeatureUnregistering(
	const UGameFeatureData* GameFeatureData, const FString& PluginName, const FString& PluginURL)
{
	const FString PluginRootPath = TEXT("/") + PluginName;

	for (const UGameFeatureAction* Action : GameFeatureData->GetActions())
	{
		if (const UGameFeatureAction_AddGameplayCuePath* AddGameplayCueGFA =
				Cast<UGameFeatureAction_AddGameplayCuePath>(GameFeatureData))
		{
			const TArray<FDirectoryPath>& DirsToAdd = AddGameplayCueGFA->DirectoryPathsToAdd;
			if (ULyraGameplayCueManager* GCM = ULyraGameplayCueManager::Get())
			{
				int32 NumRemoved = 0;
				for (const FDirectoryPath& Directory : DirsToAdd)
				{
					FString MutablePath = Directory.Path;
					UGameFeaturesSubsystem::FixPluginPackagePath(
						MutablePath, PluginRootPath, false);
					NumRemoved += GCM->RemoveGameplayCueNotifyPath(MutablePath, false);
				}

				if (NumRemoved > 0)
				{
					GCM->InitializeRuntimeObjectLibrary();
				}
			}
		}
	}
}