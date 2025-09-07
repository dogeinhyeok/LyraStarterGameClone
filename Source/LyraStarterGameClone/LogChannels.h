// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/UnrealString.h"
#include "Logging/LogMacros.h"

/**
 * Lyra 게임의 로그 카테고리를 정의하는 헤더 파일
 * 
 * 이 파일은 게임 전체에서 사용할 로그 카테고리들을 선언합니다.
 * 로그 카테고리를 사용하면 특정 모듈이나 시스템의 로그만 필터링하여 볼 수 있습니다.
 */

/**
 * Lyra 게임의 메인 로그 카테고리
 * 
 * 사용법:
 * - UE_LOG(LogLyra, Warning, TEXT("경고 메시지"));
 * - UE_LOG(LogLyra, Error, TEXT("에러 메시지"));
 * - UE_LOG(LogLyra, Log, TEXT("일반 로그 메시지"));
 * 
 * 로그 레벨:
 * - Log: 일반적인 정보성 메시지
 * - All: 모든 로그 레벨을 포함 (Verbose, VeryVerbose 포함)
 */
DECLARE_LOG_CATEGORY_EXTERN(LogLyra, Log, All);
