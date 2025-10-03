// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "../Input/LyraMappableConfigPair.h"
#include "LyraHeroComponent.generated.h"

struct FInputActionValue;
class ULyraCameraMode;

/**
 *
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class LYRASTARTERGAMECLONE_API ULyraHeroComponent :
	public UPawnComponent,
	public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	ULyraHeroComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static const FName NAME_ActorFeatureName;
	static const FName NAME_BindInputsNow;

	virtual void OnRegister() final;
	virtual void BeginPlay() final;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final;

	virtual FName GetFeatureName() const final { return NAME_ActorFeatureName; };
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) final;
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager,
		FGameplayTag CurrentState, FGameplayTag DesiredState) const final;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager,
		FGameplayTag CurrentState, FGameplayTag DesiredState) final;
	virtual void CheckDefaultInitialization() final;

	TSubclassOf<ULyraCameraMode> DetermineCameraMode() const;
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	UPROPERTY(EditAnywhere)
	TArray<FLyraMappableConfigPair> DefaultInputConfigs;
};
