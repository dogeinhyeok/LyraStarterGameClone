// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraCharacter.cpp - 메인 플레이어 캐릭터 구현
 * 기본 ACharacter를 상속받는 메인 플레이어 캐릭터 (현재는 기본 구현만)
 */

#include "LyraCharacter.h"

/**
 * ALyraCharacter 생성자 - 캐릭터의 기본 설정을 초기화
 */
ALyraCharacter::ALyraCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance
	// if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/**
 * BeginPlay - 게임 시작 시 또는 스폰될 때 호출되는 함수
 */
void ALyraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * Tick - 매 프레임마다 호출되는 함수
 */
void ALyraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * SetupPlayerInputComponent - 입력 기능을 바인딩하는 함수
 */
void ALyraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
