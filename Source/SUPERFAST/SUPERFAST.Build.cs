// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SUPERFAST : ModuleRules
{
	public SUPERFAST(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils" });

        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");

    }
}
