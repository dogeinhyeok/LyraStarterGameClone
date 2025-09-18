// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraPawnComponent_CharacterParts.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"

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

ULyraPawnComponent_CharacterParts::ULyraPawnComponent_CharacterParts(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
FLyraCharacterPartHandle ULyraPawnComponent_CharacterParts::AddCharacterPart(
	const FLyraCharacterPart& NewPart)
{
	return CharacterPartList.AddEntry(NewPart);
}

USceneComponent* ULyraPawnComponent_CharacterParts::GetSceneComponentToAttachTo() const
{
	return nullptr;
}

void ULyraPawnComponent_CharacterParts::BroadcastChanged()
{
	// 캐릭터 파트 변경 알림 (현재는 빈 구현)
}
