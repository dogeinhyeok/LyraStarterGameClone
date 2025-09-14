// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraCameraMode.h"
#include "LyraCameraMode_ThirdPerson.generated.h"

class UCurveVector;

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class LYRASTARTERGAMECLONE_API ULyraCameraMode_ThirdPerson : public ULyraCameraMode
{
	GENERATED_BODY()

public:
	ULyraCameraMode_ThirdPerson(
		const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void UpdateView(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "ThirdPerson")
	TObjectPtr<const UCurveVector> TargetOffsetCurve;
};
