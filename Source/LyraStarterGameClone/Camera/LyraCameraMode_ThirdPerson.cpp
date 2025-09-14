// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraCameraMode_ThirdPerson.h"
#include "Curves/CurveVector.h"

ULyraCameraMode_ThirdPerson::ULyraCameraMode_ThirdPerson(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULyraCameraMode_ThirdPerson::UpdateView(float DeltaTime)
{
	FVector PivotLocation = GetPivotLocation();
	FRotator PivotRotation = GetPivotRotation();

	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	if (TargetOffsetCurve)
	{
		const FVector TargetOffset = TargetOffsetCurve->GetVectorValue(PivotRotation.Pitch);
		View.Location = PivotLocation + PivotRotation.RotateVector(TargetOffset);
	}
}