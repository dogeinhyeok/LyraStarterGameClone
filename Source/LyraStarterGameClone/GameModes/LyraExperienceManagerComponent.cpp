// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraExperienceManagerComponent.cpp - Experience 관리자 컴포넌트 구현
 * Experience 로딩을 관리하고 완료 시 델리게이트를 브로드캐스트하는 컴포넌트
 */

#include "LyraExperienceManagerComponent.h"
#include "LyraExperienceDefinition.h"
#include "../System/LyraAssetManager.h"
#include "GameFeaturesSubsystemSettings.h"

/**
 * CallOrRegister_OnExperienceLoaded - Experience 로딩 완료 델리게이트 등록 또는 즉시 실행
 */
void ULyraExperienceManagerComponent::CallOrRegister_OnExperienceLoaded(
	FOnLyraExperienceLoaded::FDelegate&& Delegate)
{
	if (IsExperienceLoaded())
	{
		Delegate.ExecuteIfBound(CurrentExperience);
	}
	else
	{
		OnExperienceLoaded.Add(MoveTemp(Delegate));
	}
}

/**
 * ServerSetCurrentExperience - 서버에서 현재 Experience를 설정하고 로딩 시작
 */
void ULyraExperienceManagerComponent::ServerSetCurrentExperience(FPrimaryAssetId ExperienceId)
{
	ULyraAssetManager& AssetManager = ULyraAssetManager::Get();

	TSubclassOf<ULyraExperienceDefinition> AssetClass;
	{
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(ExperienceId);
		AssetClass = Cast<UClass>(AssetPath.TryLoad());
	}

	const ULyraExperienceDefinition* Experience = GetDefault<ULyraExperienceDefinition>(AssetClass);
	check(Experience != nullptr);
	check(CurrentExperience == nullptr);
	{
		CurrentExperience = Experience;
	}

	StartExperienceLoad();
}

UE_DISABLE_OPTIMIZATION
/**
 * StartExperienceLoad - Experience 에셋 로딩을 시작하는 함수
 */
void ULyraExperienceManagerComponent::StartExperienceLoad()
{
	check(CurrentExperience);
	check(LoadState == ELyraExperienceLoadState::Unloaded);

	LoadState = ELyraExperienceLoadState::Loading;

	ULyraAssetManager& AssetManager = ULyraAssetManager::Get();

	TSet<FPrimaryAssetId> BundleAssetList;
	BundleAssetList.Add(CurrentExperience->GetPrimaryAssetId());

	TArray<FName> BundleToLoad;
	{
		const ENetMode OwnerNetMode = GetOwner()->GetNetMode();
		bool bLoadClient = GIsEditor || (OwnerNetMode != NM_DedicatedServer);
		bool bLoadServer = GIsEditor || (OwnerNetMode == NM_Client);
		if (bLoadClient)
		{
			BundleToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateClient);
		}
		if (bLoadServer)
		{
			BundleToLoad.Add(UGameFeaturesSubsystemSettings::LoadStateServer);
		}
	}

	FStreamableDelegate OnAssetsLoadedDelegate =
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnExperienceLoadComplete);

	TSharedPtr<FStreamableHandle> Handle =
		AssetManager.ChangeBundleStateForPrimaryAssets(BundleAssetList.Array(), BundleToLoad, {},
			false, FStreamableDelegate(), FStreamableManager::AsyncLoadHighPriority);

	if (!Handle.IsValid() || Handle->HasLoadCompleted())
	{
		FStreamableHandle::ExecuteDelegate(OnAssetsLoadedDelegate);
	}
	else
	{
		Handle->BindCompleteDelegate(OnAssetsLoadedDelegate);
		Handle->BindCancelDelegate(FStreamableDelegate::CreateLambda(
			[OnAssetsLoadedDelegate] { OnAssetsLoadedDelegate.ExecuteIfBound(); }));
	}

	static int32 StartExperienceLoad_FrameNumber = GFrameNumber;
}
UE_ENABLE_OPTIMIZATION

/**
 * OnExperienceLoadComplete - Experience 로딩 완료 시 호출되는 함수
 */
void ULyraExperienceManagerComponent::OnExperienceLoadComplete()
{
	static int32 OnExperienceLoadComplete_FrameNumber = GFrameNumber;

	OnExperienceFullLoadCompleted();
}

/**
 * OnExperienceFullLoadCompleted - Experience 완전 로딩 완료 시 델리게이트 브로드캐스트
 */
void ULyraExperienceManagerComponent::OnExperienceFullLoadCompleted()
{
	check(LoadState == ELyraExperienceLoadState::Loaded);
	LoadState = ELyraExperienceLoadState::Loaded;
	OnExperienceLoaded.Broadcast(CurrentExperience);
	OnExperienceLoaded.Clear();
}

/**
 * GetCurrentExperienceChecked - 현재 로딩된 Experience를 안전하게 반환
 */
const ULyraExperienceDefinition*
ULyraExperienceManagerComponent::GetCurrentExperienceChecked() const
{
	check(LoadState == ELyraExperienceLoadState::Loaded);
	check(CurrentExperience != nullptr);
	return CurrentExperience;
}
