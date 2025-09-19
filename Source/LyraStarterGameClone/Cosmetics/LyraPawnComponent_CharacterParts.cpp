// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraPawnComponent_CharacterParts.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ULyraPawnComponent_CharacterParts::ULyraPawnComponent_CharacterParts(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), CharacterPartList(this)
{
}

USkeletalMeshComponent* ULyraPawnComponent_CharacterParts::GetParentMeshComponent() const
{
	if (AActor* OwnerActor = GetOwner())
	{
		if (ACharacter* OwningCharacter = Cast<ACharacter>(OwnerActor))
		{
			if (USkeletalMeshComponent* MeshComponent = OwningCharacter->GetMesh())
			{
				return MeshComponent;
			}
		}
	}

	return nullptr;
}

USceneComponent* ULyraPawnComponent_CharacterParts::GetSceneComponentToAttachTo() const
{
	if (USkeletalMeshComponent* MeshComponent = GetParentMeshComponent())
	{
		return Cast<USceneComponent>(MeshComponent);
	}

	if (AActor* OwnerActor = GetOwner())
	{
		return OwnerActor->GetRootComponent();
	}

	return nullptr;
}

FGameplayTagContainer ULyraPawnComponent_CharacterParts::GetCombinedTags(
	FGameplayTag RequiredPrefix) const
{
	FGameplayTagContainer Result = CharacterPartList.CollectCombinedTags();
	if (RequiredPrefix.IsValid())
	{
		return Result.Filter(FGameplayTagContainer(RequiredPrefix));
	}
	else
	{
		return Result;
	}
}

void ULyraPawnComponent_CharacterParts::BroadcastChanged()
{
	const bool bReinitPose = true;

	if (USkeletalMeshComponent* MeshComponent = GetParentMeshComponent())
	{
		const FGameplayTagContainer MergedTags = GetCombinedTags(FGameplayTag());
		USkeletalMesh* DesiredMesh = BodyMeshes.SelectBestBodyStyle(MergedTags);

		MeshComponent->SetSkeletalMesh(DesiredMesh, bReinitPose);

		if (UPhysicsAsset* PhysicsAsset = BodyMeshes.ForcedPhysicsAsset)
		{
			MeshComponent->SetPhysicsAsset(PhysicsAsset, bReinitPose);
		}
	}
}

FLyraCharacterPartHandle ULyraPawnComponent_CharacterParts::AddCharacterPart(
	const FLyraCharacterPart& NewPart)
{
	return CharacterPartList.AddEntry(NewPart);
}

void ULyraPawnComponent_CharacterParts::RemoveCharacterPart(FLyraCharacterPartHandle Handle)
{
	CharacterPartList.RemoveEntry(Handle);
}

bool FLyraCharacterPartList::SpawnActorForEntry(FLyraAppliedCharacterPartEntry& Entry)
{
	bool bCreatedAnyActor = false;

	if (Entry.Part.PartClass != nullptr)
	{
		UWorld* World = OwnerComponent->GetWorld();

		if (USceneComponent* ComponentToAttachTo = OwnerComponent->GetSceneComponentToAttachTo())
		{
			const FTransform SpawnTransform =
				ComponentToAttachTo->GetSocketTransform(Entry.Part.SocketName);

			UChildActorComponent* PartComponent =
				NewObject<UChildActorComponent>(OwnerComponent->GetOwner());
			PartComponent->SetupAttachment(ComponentToAttachTo, Entry.Part.SocketName);
			PartComponent->SetChildActorClass(Entry.Part.PartClass);
			PartComponent->RegisterComponent();

			if (AActor* SpawnedActor = PartComponent->GetChildActor())
			{
				if (USceneComponent* SpawnedRootComponent = SpawnedActor->GetRootComponent())
				{
					SpawnedRootComponent->AddTickPrerequisiteComponent(ComponentToAttachTo);
				}
			}

			Entry.SpawnedComponent = PartComponent;
			bCreatedAnyActor = true;
		}
	}
	return bCreatedAnyActor;
}

FLyraCharacterPartHandle FLyraCharacterPartList::AddEntry(FLyraCharacterPart NewPart)
{
	FLyraCharacterPartHandle Result;
	Result.PartHandle = PartHandleCounter++;

	if (ensure(OwnerComponent && OwnerComponent->GetOwner()
			&& OwnerComponent->GetOwner()->HasAuthority()))
	{
		FLyraAppliedCharacterPartEntry& NewEntry = Entries.AddDefaulted_GetRef();
		NewEntry.Part = NewPart;
		NewEntry.PartHandle = Result.PartHandle;

		if (SpawnActorForEntry(NewEntry))
		{
			OwnerComponent->BroadcastChanged();
		}
	}
	return Result;
}

void FLyraCharacterPartList::DestroyActorForEntry(FLyraAppliedCharacterPartEntry& Entry)
{
	if (Entry.SpawnedComponent)
	{
		Entry.SpawnedComponent->DestroyComponent();
		Entry.SpawnedComponent = nullptr;
	}
}

FGameplayTagContainer FLyraCharacterPartList::CollectCombinedTags() const
{
	FGameplayTagContainer Result;

	for (const FLyraAppliedCharacterPartEntry& Entry : Entries)
	{
		if (Entry.SpawnedComponent)
		{
			if (IGameplayTagAssetInterface* TagInterface =
					Cast<IGameplayTagAssetInterface>(Entry.SpawnedComponent->GetChildActor()))
			{
				TagInterface->GetOwnedGameplayTags(Result);
			}
		}
	}

	return Result;
}

void FLyraCharacterPartList::RemoveEntry(FLyraCharacterPartHandle Handle)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FLyraAppliedCharacterPartEntry& Entry = *EntryIt;

		if (Entry.PartHandle == Handle.PartHandle)
		{
			DestroyActorForEntry(Entry);
		}
	}
}
