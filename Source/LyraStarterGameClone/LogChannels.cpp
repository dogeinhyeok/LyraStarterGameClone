// Fill out your copyright notice in the Description page of Project Settings.

#include "LogChannels.h"

/**
 * LogChannels.cpp - 로그 카테고리 구현 파일
 *
 * 이 파일은 LogChannels.h에서 선언된 로그 카테고리들을 실제로 정의합니다.
 * 헤더 파일에서는 DECLARE_LOG_CATEGORY_EXTERN으로 선언만 하고,
 * 이 파일에서 DEFINE_LOG_CATEGORY로 실제 구현을 제공합니다.
 */

/**
 * LogLyra 로그 카테고리를 정의합니다
 *
 * 이 매크로는 다음과 같은 기능을 제공합니다:
 * - 로그 카테고리 인스턴스 생성
 * - 로그 레벨 설정 (Log, All)
 * - 런타임에서 로그 필터링 가능
 *
 * 사용 예시:
 * UE_LOG(LogLyra, Warning, TEXT("Asset loading failed: %s"), *AssetName);
 * UE_LOG(LogLyra, Error, TEXT("Critical error in %s"), TEXT("GameplaySystem"));
 */
DEFINE_LOG_CATEGORY(LogLyra);
