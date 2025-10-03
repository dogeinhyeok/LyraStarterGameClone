// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "LyraPawnExtensionComponent.generated.h"

class ULyraPawnData;
class ULyraAbilitySystemComponent;

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraPawnExtensionComponent :
	public UPawnComponent,
	public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	ULyraPawnExtensionComponent(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static const FName NAME_ActorFeatureName;

	static ULyraPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor)
	{
		return (Actor ? Actor->FindComponentByClass<ULyraPawnExtensionComponent>() : nullptr);
	}

	template <class T> const T* GetPawnData() const { return Cast<T>(PawnData); }
	void SetPawnData(const ULyraPawnData* InPawnData);
	void SetupPlayerInputComponent();
	ULyraAbilitySystemComponent* GetLyraAbilitySystemComponent() const
	{
		return AbilitySystemComponent;
	}

	void InitializeAbilitySystem(
		ULyraAbilitySystemComponent* InAbilitySystemComponent, AActor* InOwnerActor);
	void UninitializeAbilitySystem();

	virtual void OnRegister() final;
	virtual void BeginPlay() final;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) final;

	virtual FName GetFeatureName() const final { return NAME_ActorFeatureName; };
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) final;
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager,
		FGameplayTag CurrentState, FGameplayTag DesiredState) const final;
	virtual void CheckDefaultInitialization() final;

	UPROPERTY(EditInstanceOnly, Category = "Lyra|Pawn")
	TObjectPtr<const ULyraPawnData> PawnData;

	UPROPERTY()
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent;
};
