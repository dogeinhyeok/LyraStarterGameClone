// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManager.generated.h"

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
	static AssetType* GetAsset(
		const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(
		const TSoftClassPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	void AddLoadedAsset(const UObject* Asset);

	UPROPERTY()
	TSet<TSoftObjectPtr<UObject>> LoadedAssets;

	FCriticalSection SyncObject;
};

/**
 * GetAsset - 소프트 포인터로부터 에셋을 로딩하고 반환하는 템플릿 함수
 */
template <typename AssetType>
AssetType* ULyraAssetManager::GetAsset(
	const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	// 소프트 포인터에서 실제 에셋 경로를 추출
	const FSoftObjectPath AssetPath = AssetPointer.ToSoftObjectPath();

	// 에셋 경로의 유효성 검증
	if (AssetPath.IsValid())
	{
		// 소프트 포인터에서 실제 에셋 객체를 가져옴
		LoadedAsset = AssetPointer.Get();

		// 에셋이 아직 로딩되지 않은 경우 동기적 로딩 수행
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			// 로딩 실패 시 상세한 에러 메시지와 함께 어서션 발생
			ensureAlwaysMsgf(
				LoadedAsset, TEXT("Failed to load asset: [%s]"), *AssetPath.ToString());
		}

		// 에셋 로딩 성공 및 메모리 유지 옵션이 활성화된 경우
		if (LoadedAsset && bkeepInMemory)
		{
			// 로딩된 에셋을 관리 목록에 등록하여 가비지 컬렉션으로부터 보호
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}

	return LoadedAsset;
}

/**
 * GetSubclass - 소프트 포인터로부터 서브클래스를 로딩하고 반환하는 템플릿 함수
 */
template <typename AssetType>
TSubclassOf<AssetType> ULyraAssetManager::GetSubclass(
	const TSoftClassPtr<AssetType>& AssetPointer, bool bkeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass = nullptr;
	// 소프트 포인터에서 실제 클래스 경로를 가져옴
	const FSoftObjectPath AssetPath = AssetPointer.ToSoftObjectPath();

	// 클래스 경로가 유효한지 확인
	if (AssetPath.IsValid())
	{
		// 소프트 포인터에서 실제 클래스 객체를 가져옴
		LoadedSubclass = AssetPointer.Get();

		// 클래스가 아직 로딩되지 않았다면 동기적으로 로딩 시도
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			// 클래스 로딩 실패 시 에러 메시지 출력
			ensureAlwaysMsgf(
				LoadedSubclass, TEXT("Failed to load subclass : [%s]"), *AssetPath.ToString());
		}
	}

	// 클래스가 성공적으로 로딩되었고 메모리에 유지하도록 설정된 경우
	if (LoadedSubclass && bkeepInMemory)
	{
		// 로딩된 클래스를 목록에 추가하여 메모리에서 해제되지 않도록 함
		Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
	}

	return LoadedSubclass;
}
