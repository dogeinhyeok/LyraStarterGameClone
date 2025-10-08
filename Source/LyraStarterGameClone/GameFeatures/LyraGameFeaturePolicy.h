#pragma once

#include "Containers/Array.h"
#include "GameFeatureStateChangeObserver.h"
#include "GameFeaturesProjectPolicies.h"
#include "UObject/Object.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include "LyraGameFeaturePolicy.generated.h"

UCLASS()
class ULyraGameFeaturePolicy : public UDefaultGameFeaturesProjectPolicies
{
	GENERATED_BODY()

public:
	ULyraGameFeaturePolicy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void InitGameFeatureManager() override;
	virtual void ShutdownGameFeatureManager() override;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UObject>> Observers;
};

UCLASS()
class ULyraGameFeature_AddGameplayCuePaths : public UObject, public IGameFeatureStateChangeObserver
{
	GENERATED_BODY()

public:
	virtual void OnGameFeatureRegistering(const UGameFeatureData* GameFeatureData,
		const FString& PluginName, const FString& PluginURL) override;

	virtual void OnGameFeatureUnregistering(const UGameFeatureData* GameFeatureData,
		const FString& PluginName, const FString& PluginURL) override;
};