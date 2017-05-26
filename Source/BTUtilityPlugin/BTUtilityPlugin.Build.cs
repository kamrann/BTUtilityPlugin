// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BTUtilityPlugin : ModuleRules
{
	public BTUtilityPlugin(ReadOnlyTargetRules Target): base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.Add("BTUtilityPlugin/Private");

		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "AIModule",
				"GameplayTasks"
            }
        );
	}
}
