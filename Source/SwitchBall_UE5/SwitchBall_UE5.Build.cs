// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SwitchBall_UE5 : ModuleRules
{
	public SwitchBall_UE5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
        PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks" });
    }
}
