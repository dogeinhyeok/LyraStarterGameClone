// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManager.generated.h"

/**
 * Lyra 게임의 에셋 관리를 담당하는 커스텀 AssetManager 클래스
 *
 * 주요 기능:
 * - 에셋의 동기/비동기 로딩 관리
 * - 로딩된 에셋의 메모리 추적
 * - 게임 시작 시 초기 에셋 로딩
 * - 에셋 로딩 성능 측정 및 로깅
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	/**
	 * AssetManager 싱글톤 인스턴스를 가져옵니다
	 * @return ULyraAssetManager의 참조
	 */
	static ULyraAssetManager& Get();

	/**
	 * 게임 시작 시 초기 에셋들을 로딩합니다
	 * final 키워드로 오버라이드 방지
	 */
	virtual void StartInitialLoading() final;

	/**
	 * 에셋 로딩 로그를 출력할지 결정합니다
	 * @return 로그 출력 여부
	 */
	static bool ShouldLogAssetLoads();

	/**
	 * 에셋을 동기적으로 로딩합니다 (로딩 완료까지 대기)
	 * @param AssetPath 로딩할 에셋의 경로
	 * @return 로딩된 에셋 객체, 실패 시 nullptr
	 */
	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/**
	 * 템플릿 함수: 특정 타입의 에셋을 가져옵니다
	 * @tparam AssetType 가져올 에셋의 타입
	 * @param AssetPointer 에셋을 가리키는 소프트 포인터
	 * @param bkeepInMemory 메모리에 유지할지 여부 (기본값: true)
	 * @return 로딩된 에셋 객체
	 */
	template <typename AssetType>
	static AssetType* GetAsset(
		const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	/**
	 * 템플릿 함수: 특정 타입의 서브클래스를 가져옵니다
	 * @tparam AssetType 가져올 클래스의 부모 타입
	 * @param AssetPointer 클래스를 가리키는 소프트 포인터
	 * @param bkeepInMemory 메모리에 유지할지 여부 (기본값: true)
	 * @return 로딩된 서브클래스
	 */
	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(
		const TSoftClassPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	/**
	 * 로딩된 에셋을 관리 목록에 추가합니다
	 * @param Asset 추가할 에셋 객체
	 */
	void AddLoadedAsset(const UObject* Asset);

	/**
	 * 현재 로딩된 모든 에셋들을 저장하는 컨테이너
	 * 메모리 관리와 에셋 추적을 위해 사용
	 */
	UPROPERTY()
	TSet<TSoftObjectPtr<UObject>> LoadedAssets;

	/**
	 * 멀티스레드 환경에서 LoadedAssets에 안전하게 접근하기 위한 동기화 객체
	 */
	FCriticalSection SyncObject;
};

/**
 * 템플릿 함수 구현: 특정 타입의 에셋을 가져옵니다
 * @tparam AssetType 가져올 에셋의 타입
 * @param AssetPointer 에셋을 가리키는 소프트 포인터
 * @param bkeepInMemory 메모리에 유지할지 여부
 * @return 로딩된 에셋 객체
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
 * 템플릿 함수 구현: 특정 타입의 서브클래스를 가져옵니다
 * @tparam AssetType 가져올 클래스의 부모 타입
 * @param AssetPointer 클래스를 가리키는 소프트 포인터
 * @param bkeepInMemory 메모리에 유지할지 여부
 * @return 로딩된 서브클래스
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
