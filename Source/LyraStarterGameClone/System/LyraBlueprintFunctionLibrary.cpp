// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraBlueprintFunctionLibrary.h"
#include "LyraStarterGameClone/LogChannels.h"
#include "HAL/UnrealMemory.h"
#include "Misc/OutputDevice.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

/**
 * LyraBlueprintFunctionLibrary.cpp - 블루프린트 유틸리티 함수 구현
 * 
 * 이 파일은 블루프린트에서 언리얼 엔진의 다양한 기능을 쉽게 사용할 수 있도록
 * 도와주는 유틸리티 함수들을 구현합니다.
 */

void ULyraBlueprintFunctionLibrary::PrintLog(const UObject* WorldContextObject, const FText InText, bool bPrintToScreen, bool bPrintToLog, 
	FLinearColor TextColor, float Duration, const FName Key)
{
#if !UE_BUILD_SHIPPING
	if (bPrintToLog)
	{
		FString ObjectName = GetNameSafe(WorldContextObject);
		UE_LOG(LogLyra, Log, TEXT("[%s] %s"), *ObjectName, *InText.ToString());
	}
	
	if (bPrintToScreen && GEngine)
	{
		uint64 InnerKey = -1;
		if (Key != NAME_None)
		{
			InnerKey = GetTypeHash(Key);
		}
		GEngine->AddOnScreenDebugMessage(InnerKey, Duration, TextColor.ToFColor(true), InText.ToString());
	}
#endif
}

void ULyraBlueprintFunctionLibrary::PrintWarning(const UObject* WorldContextObject, const FText InText, bool bPrintToScreen, bool bPrintToLog, 
	FLinearColor TextColor, float Duration, const FName Key)
{
#if !UE_BUILD_SHIPPING
	if (bPrintToLog)
	{
		FString ObjectName = GetNameSafe(WorldContextObject);
		UE_LOG(LogLyra, Warning, TEXT("[%s] %s"), *ObjectName, *InText.ToString());
	}
	
	if (bPrintToScreen && GEngine)
	{
		uint64 InnerKey = -1;
		if (Key != NAME_None)
		{
			InnerKey = GetTypeHash(Key);
		}
		GEngine->AddOnScreenDebugMessage(InnerKey, Duration, TextColor.ToFColor(true), InText.ToString());
	}
#endif
}

void ULyraBlueprintFunctionLibrary::PrintError(const UObject* WorldContextObject, const FText InText, bool bPrintToScreen, bool bPrintToLog, 
	FLinearColor TextColor, float Duration, const FName Key)
{
#if !UE_BUILD_SHIPPING
	if (bPrintToLog)
	{
		FString ObjectName = GetNameSafe(WorldContextObject);
		UE_LOG(LogLyra, Error, TEXT("[%s] %s"), *ObjectName, *InText.ToString());
	}
	
	if (bPrintToScreen && GEngine)
	{
		uint64 InnerKey = -1;
		if (Key != NAME_None)
		{
			InnerKey = GetTypeHash(Key);
		}
		GEngine->AddOnScreenDebugMessage(InnerKey, Duration, TextColor.ToFColor(true), InText.ToString());
	}
#endif
}