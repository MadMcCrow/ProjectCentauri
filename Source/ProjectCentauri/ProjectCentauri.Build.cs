// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectCentauri : ModuleRules
{
	public ProjectCentauri(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        // PublicDependencyModuleNames.AddRange(new string[] { "StreamingPauseRendering", "OnlineSubsystem", "OnlineSubsystemUtils" });

        // Load screen
        PrivateDependencyModuleNames.AddRange(new string[] { "StreamingPauseRendering" });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        //Improve compile speeds
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

    }
}
