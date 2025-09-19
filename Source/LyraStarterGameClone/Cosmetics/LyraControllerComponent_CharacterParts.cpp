// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraControllerComponent_CharacterParts.h"
#include "GameFramework/Controller.h"
#include "LyraPawnComponent_CharacterParts.h"

ULyraControllerComponent_CharacterParts::ULyraControllerComponent_CharacterParts(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULyraControllerComponent_CharacterParts::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (AController* OwningController = GetController<AController>())
		{
			OwningController->OnPossessedPawnChanged.AddDynamic(
				this, &ThisClass::OnPossessedPawnChanged);
		}
	}
}

void ULyraControllerComponent_CharacterParts::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

ULyraPawnComponent_CharacterParts*
ULyraControllerComponent_CharacterParts::GetPawnCustomizer() const
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		return ControlledPawn->FindComponentByClass<ULyraPawnComponent_CharacterParts>();
	}
	return nullptr;
}

void ULyraControllerComponent_CharacterParts::AddCharacterPart(const FLyraCharacterPart& NewPart)
{
	AddCharacterPartInternal(NewPart);
}

void ULyraControllerComponent_CharacterParts::AddCharacterPartInternal(
	const FLyraCharacterPart& NewPart)
{
	FLyraControllerCharacterPartEntry& NewEntry = CharacterParts.AddDefaulted_GetRef();
	NewEntry.Part = NewPart;

	if (ULyraPawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		NewEntry.Handle = PawnCustomizer->AddCharacterPart(NewPart);
	}
}

void ULyraControllerComponent_CharacterParts::RemoveAllCharacterParts()
{
	if (ULyraPawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		for (FLyraControllerCharacterPartEntry& Entry : CharacterParts)
		{
			PawnCustomizer->RemoveCharacterPart(Entry.Handle);
		}
	}
	CharacterParts.Reset();
}

void ULyraControllerComponent_CharacterParts::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (ULyraPawnComponent_CharacterParts* OldCustomizer =
			OldPawn ? OldPawn->FindComponentByClass<ULyraPawnComponent_CharacterParts>() : nullptr)
	{
		for (FLyraControllerCharacterPartEntry& Entry : CharacterParts)
		{
			OldCustomizer->RemoveCharacterPart(Entry.Handle);
			Entry.Handle.Reset();
		}
	}

	if (ULyraPawnComponent_CharacterParts* NewCustomizer =
			NewPawn ? NewPawn->FindComponentByClass<ULyraPawnComponent_CharacterParts>() : nullptr)
	{
		for (FLyraControllerCharacterPartEntry& Entry : CharacterParts)
		{
			check(!Entry.Handle.IsValid());
			Entry.Handle = NewCustomizer->AddCharacterPart(Entry.Part);
		}
	}
}
