// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Equipment/LyraGameplayAbility_FromEquipment.h"
#include "LyraGameplayAbility_RangedWeapon.generated.h"

class ULyraRangedWeaponInstance;

UENUM(BlueprintType)
enum class ELyraAbilityTargetingSource : uint8
{
	CameraTowardsFocus,
};

/**
 *
 */
UCLASS()
class LYRASTARTERGAMECLONE_API ULyraGameplayAbility_RangedWeapon :
	public ULyraGameplayAbility_FromEquipment
{
	GENERATED_BODY()

public:
	struct FRangedWeaponFiringInput
	{
		FVector StartTrace;
		FVector EndAim;
		FVector AimDir;
		ULyraRangedWeaponInstance* WeaponData = nullptr;
		bool bCanPlayBulletFX = false;

		FRangedWeaponFiringInput()
			: StartTrace(ForceInitToZero), EndAim(ForceInitToZero), AimDir(ForceInitToZero)
		{
		}
	};

	ULyraGameplayAbility_RangedWeapon(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	void StartRangedWeaponTargeting();

	void PerformLocalTargeting(TArray<FHitResult>& OutHits);
	FTransform GetTargetingTransform(APawn* SourcePawn, ELyraAbilityTargetingSource Source);
	FVector GetWeaponTargetingSourceLocation() const;
	void TraceBulletsInCartridge(
		const FRangedWeaponFiringInput& InputData, TArray<FHitResult>& OutHits);
	FHitResult DoSingleBulletTrace(const FVector& StartTrace, const FVector& EndTrace,
		float SweepRadius, bool bIsSimulated, TArray<FHitResult>& OutHits);
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace, float SweepRadius,
		bool bIsSimulated, TArray<FHitResult>& OutHitResults) const;
	ECollisionChannel DetermineTraceChannel(
		FCollisionQueryParams& TraceParams, bool bIsSimulated) const;
	void AddAdditionalTraceIgnoreActors(FCollisionQueryParams& TraceParams) const;
	void OnTargetDataReadyCallback(
		const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRangedWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	ULyraRangedWeaponInstance* GetWeaponInstance();
};
