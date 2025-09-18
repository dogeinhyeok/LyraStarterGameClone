// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraControllerComponent_CharacterParts.h"
#include "LyraPawnComponent_CharacterParts.h"

ULyraControllerComponent_CharacterParts::ULyraControllerComponent_CharacterParts(
	const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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