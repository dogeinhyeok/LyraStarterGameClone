// Fill out your copyright notice in the Description page of Project Settings.

/**
 * LyraPlayerState.cpp - 플레이어 상태 구현
 * Experience 로딩 시 PawnData를 설정하고 관리하는 클래스
 */

#include "LyraPlayerState.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "../AbilitySystem/LyraAbilitySystemComponent.h"
#include "../GameModes/LyraExperienceManagerComponent.h"
#include "../GameModes/LyraGameModeBase.h"
#include "../Character/LyraPawnData.h"
#include "../AbilitySystem/LyraAbilitySet.h"

ALyraPlayerState::ALyraPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<ULyraAbilitySystemComponent>(
		this, TEXT("AbilitySystemComponent"));
}

/**
 * PostInitializeComponents - 컴포넌트 초기화 후 Experience 델리게이트 등록
 */
void ALyraPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	{
		FGameplayAbilityActorInfo* ActorInfo = AbilitySystemComponent->AbilityActorInfo.Get();
		check(ActorInfo->OwnerActor == this);
		check(ActorInfo->OwnerActor == ActorInfo->AvatarActor);
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	ULyraExperienceManagerComponent* ExperienceManagerComponent =
		GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(
		FOnLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

/**
 * OnExperienceLoaded - Experience 로딩 완료 시 PawnData 설정
 */
void ALyraPlayerState::OnExperienceLoaded(const ULyraExperienceDefinition* CurrentExperience)
{
	if (ALyraGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ALyraGameModeBase>())
	{
		const ULyraPawnData* NewPawnData =
			GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

/**
 * SetPawnData - 플레이어의 Pawn 데이터를 설정하는 함수
 */
void ALyraPlayerState::SetPawnData(const ULyraPawnData* InPawnData)
{
	check(InPawnData);

	check(!PawnData);

	PawnData = InPawnData;

	for (ULyraAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (!AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}
}
