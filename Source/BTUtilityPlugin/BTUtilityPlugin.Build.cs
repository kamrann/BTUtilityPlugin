// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BTUtilityPlugin : ModuleRules
{
	public BTUtilityPlugin(TargetInfo Target)
	{
        PrivateIncludePaths.Add("BTUtilityPlugin/Private");

		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "AIModule"
            }
        );
	}
}
