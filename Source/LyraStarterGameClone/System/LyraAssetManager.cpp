// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraAssetManager.h"
#include "Engine/Engine.h"
#include "Misc/CommandLine.h"
#include "../LogChannels.h"

/**
 * AssetManager 싱글톤 인스턴스를 가져오는 함수
 * 언리얼 엔진의 전역 AssetManager가 우리가 만든 LyraAssetManager인지 확인하고 반환
 */
ULyraAssetManager& ULyraAssetManager::Get()
{
	// GEngine이 존재하는지 확인 (게임이 제대로 초기화되었는지 체크)
	check(GEngine)

	// GEngine의 AssetManager가 우리가 만든 LyraAssetManager 타입인지 확인
	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		// 맞다면 해당 인스턴스를 반환
		return *Singleton;
	}

	// DefaultEngine.ini에서 AssetManager 설정이 잘못되었을 때 에러 로그
	UE_LOG(LogLyra, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be LyraAssetManager!"));

	// 비상용으로 새 인스턴스 생성 (일반적으로는 위에서 반환됨)
	return *NewObject<ULyraAssetManager>();
}

/**
 * 에셋 로딩 로그를 출력할지 결정하는 함수
 * 명령줄에 -LogAssetLoads 파라미터가 있으면 로그를 출력
 */
bool ULyraAssetManager::ShouldLogAssetLoads()
{
	// 현재 실행 중인 프로그램의 명령줄 인수들을 가져옴
	const TCHAR* CommandLineContent = FCommandLine::Get();
	
	// 명령줄에서 "LogAssetLoads" 파라미터가 있는지 확인
	// static으로 한 번만 계산하고 결과를 캐시
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	
	// 현재는 항상 true를 반환 (디버깅용)
	return true;
}

/**
 * 게임 시작 시 초기 에셋들을 로딩하는 함수
 * UE_DISABLE_OPTIMIZATION: 컴파일러 최적화를 비활성화 (디버깅이나 성능 측정 시 유용)
 */
UE_DISABLE_OPTIMIZATION
void ULyraAssetManager::StartInitialLoading()
{
	// 부모 클래스(UAssetManager)의 초기 로딩 함수 호출
	// 이 함수에서 기본적인 에셋들을 먼저 로딩함
	Super::StartInitialLoading();
}
UE_ENABLE_OPTIMIZATION

/**
 * 에셋을 동기적으로 로딩하는 함수 (로딩이 완료될 때까지 기다림)
 * @param AssetPath 로딩할 에셋의 경로
 * @return 로딩된 에셋 객체, 실패 시 nullptr
 */
UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// 에셋 경로가 유효한지 확인
	if (AssetPath.IsAsset())
	{
		// 로딩 시간을 측정하기 위한 로그 타임 객체
		TUniquePtr<FScopeLogTime> LogTimePtr;
		
		// 로그 출력이 활성화되어 있다면 로딩 시간 측정 시작
		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(
				*FString::Printf(TEXT("SynchronousLoadAsset [%s]"), *AssetPath.ToString()), 
				nullptr, 
				FScopeLogTime::ScopeLog_Seconds
			);
		}
		
		// AssetManager가 초기화되었는지 확인
		if (UAssetManager::IsInitialized())
		{
			// StreamableManager를 통해 동기적으로 에셋 로딩
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}
		
		// AssetManager가 초기화되지 않았다면 직접 로딩 시도
		return AssetPath.TryLoad();
	}
	
	// 유효하지 않은 에셋 경로면 nullptr 반환
	return nullptr;
}

/**
 * 로딩된 에셋을 관리 목록에 추가하는 함수
 * 메모리 관리와 에셋 추적을 위해 사용됨
 * @param Asset 추가할 에셋 객체
 */
void ULyraAssetManager::AddLoadedAsset(const UObject* Asset)
{
	// 에셋이 유효한지 확인 (nullptr이면 에러 발생)
	if (ensureAlways(Asset))
	{
		// 멀티스레드 환경에서 안전하게 접근하기 위한 락
		FScopeLock Lock(&SyncObject);
		
		// 로딩된 에셋 목록에 추가 (const_cast로 const 제거)
		LoadedAssets.Add(const_cast<UObject*>(Asset));
	}
}