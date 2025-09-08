// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Logging/LogVerbosity.h"
#include "LyraBlueprintFunctionLibrary.generated.h"

/**
 * Lyra 게임의 블루프린트 유틸리티 함수들을 제공하는 Function Library
 * 
 * 이 클래스는 블루프린트에서 언리얼 엔진의 다양한 기능을 쉽게 사용할 수 있도록
 * 도와주는 유틸리티 함수들을 제공합니다.
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * 일반 로그 출력 함수 (Log 레벨)
	 * @param InString 출력할 로그 메시지
	 * @param bPrintToScreen 화면에 출력할지 여부
	 * @param bPrintToLog 로그 파일에 출력할지 여부
	 * @param TextColor 화면 출력 시 텍스트 색상
	 * @param Duration 화면 출력 지속시간 (초)
	 * @param Key 화면 메시지 식별 키 (같은 키로 메시지 덮어쓰기 가능)
	 */
	UFUNCTION(BlueprintCallable, Category = "Logging", CallInEditor, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static void LyraPrintLog(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen = true, bool bPrintToLog = true, 
		FLinearColor TextColor = FLinearColor(0.0f, 0.831f, 1.0f, 1.0f), float Duration = 2.0f, const FName Key = NAME_None
	);

	UFUNCTION(BlueprintCallable, Category = "Logging", CallInEditor, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static void LyraPrintWarning(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen = true, bool bPrintToLog = true, 
		FLinearColor TextColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f), float Duration = 2.0f, const FName Key = NAME_None);

	UFUNCTION(BlueprintCallable, Category = "Logging", CallInEditor, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject"))
	static void LyraPrintError(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen = true, bool bPrintToLog = true, 
		FLinearColor TextColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), float Duration = 2.0f, const FName Key = NAME_None);
};
