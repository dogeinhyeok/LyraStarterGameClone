// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerController.h"
#include "LyraPlayerController.generated.h"

/**
 * 플레이어 컨트롤러: 기본 APlayerController를 상속받는 클래스 (현재는 빈 클래스)
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ALyraPlayerController : public AModularPlayerController
{
	GENERATED_BODY()

public:
	ALyraPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
