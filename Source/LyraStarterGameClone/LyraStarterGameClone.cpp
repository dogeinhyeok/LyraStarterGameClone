// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraStarterGameClone.h"
#include "Modules/ModuleManager.h"

class FLyraStarterGameCloneModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FLyraStarterGameCloneModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogTemp, Warning, TEXT("StartupModule!!!"));
}

void FLyraStarterGameCloneModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}

IMPLEMENT_PRIMARY_GAME_MODULE( FLyraStarterGameCloneModule, LyraStarterGameClone, "LyraStarterGameClone" );
