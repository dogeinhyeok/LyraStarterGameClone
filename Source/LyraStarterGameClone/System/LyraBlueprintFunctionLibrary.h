// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LyraBlueprintFunctionLibrary.generated.h"

UCLASS()
class LYRASTARTERGAMECLONE_API ULyraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Development", CallInEditor,
		meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject",
			DevelopmentOnly = "true",
			AdvancedDisplay = "bPrintToScreen, bPrintToLog, TextColor, Duration, Key"))
	static void PrintLog(const UObject* WorldContextObject, const FText InText = INVTEXT("Hello"),
		bool bPrintToScreen = true, bool bPrintToLog = true,
		FLinearColor TextColor = FLinearColor(0.0f, 0.831f, 1.0f, 1.0f), float Duration = 2.0f,
		const FName Key = NAME_None);

	UFUNCTION(BlueprintCallable, Category = "Development", CallInEditor,
		meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject",
			DevelopmentOnly = "true",
			AdvancedDisplay = "bPrintToScreen, bPrintToLog, TextColor, Duration, Key"))
	static void PrintWarning(const UObject* WorldContextObject,
		const FText InText = INVTEXT("Hello"), bool bPrintToScreen = true, bool bPrintToLog = true,
		FLinearColor TextColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f), float Duration = 2.0f,
		const FName Key = NAME_None);

	UFUNCTION(BlueprintCallable, Category = "Development", CallInEditor,
		meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject",
			DevelopmentOnly = "true",
			AdvancedDisplay = "bPrintToScreen, bPrintToLog, TextColor, Duration, Key"))
	static void PrintError(const UObject* WorldContextObject, const FText InText = INVTEXT("Hello"),
		bool bPrintToScreen = true, bool bPrintToLog = true,
		FLinearColor TextColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), float Duration = 2.0f,
		const FName Key = NAME_None);
};
