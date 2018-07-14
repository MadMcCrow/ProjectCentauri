// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectCentauri : ModuleRules
{
	public ProjectCentauri(ReadOnlyTargetRules Target) : base(Target)
	{
        //Improve compile speeds
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;


        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

  
    }
}
