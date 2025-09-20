// Copyright Epic Games, Inc. All Rights Reserved.

using System.Collections.Generic;
using UnrealBuildTool;

public class LyraStarterGameCloneTarget : TargetRules
{
	public LyraStarterGameCloneTarget(TargetInfo Target)
		: base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		ExtraModuleNames.Add("LyraStarterGameClone");
	}
}
