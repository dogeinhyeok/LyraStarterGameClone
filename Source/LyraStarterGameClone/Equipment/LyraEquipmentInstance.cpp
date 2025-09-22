// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraEquipmentInstance.h"
#include "LyraEquipmentDefinition.h"
#include "GameFramework/Character.h"
#include "../LogChannels.h"
#include "Engine/World.h"

ULyraEquipmentInstance::ULyraEquipmentInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

APawn* ULyraEquipmentInstance::GetPawn() const
{
	return Cast<APawn>(GetOuter());
}

void ULyraEquipmentInstance::SpawnEquipmentActors(
	const TArray<FLyraEquipmentActorToSpawn>& ActorsToSpawn)
{
	if (APawn* OwningPawn = GetPawn())
	{
		USceneComponent* AttachTarget = OwningPawn->GetRootComponent();
		if (ACharacter* Character = Cast<ACharacter>(OwningPawn))
		{
			AttachTarget = Cast<USceneComponent>(Character->GetMesh());
		}

		for (const FLyraEquipmentActorToSpawn& SpawnInfo : ActorsToSpawn)
		{
			if (SpawnInfo.ActorToSpawn)
			{
				AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(
					SpawnInfo.ActorToSpawn, FTransform::Identity, OwningPawn);
				NewActor->FinishSpawning(FTransform::Identity, true);

				NewActor->SetActorRelativeTransform(SpawnInfo.AttachTransform);

				NewActor->AttachToComponent(AttachTarget,
					FAttachmentTransformRules::KeepRelativeTransform, SpawnInfo.AttachSocket);

				SpawnedActors.Add(NewActor);
			}
		}
	}
}

void ULyraEquipmentInstance::DestroyEquipmentActors()
{
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}
}

void ULyraEquipmentInstance::OnEquipped()
{
	K2_OnEquipped();
}

void ULyraEquipmentInstance::OnUnequipped()
{
	K2_OnUnequipped();
}
