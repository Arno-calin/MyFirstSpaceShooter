// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MySpaceShooterTp1 : ModuleRules
{
	public MySpaceShooterTp1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MySpaceShooterTp1",
			"MySpaceShooterTp1/Variant_Platforming",
			"MySpaceShooterTp1/Variant_Platforming/Animation",
			"MySpaceShooterTp1/Variant_Combat",
			"MySpaceShooterTp1/Variant_Combat/AI",
			"MySpaceShooterTp1/Variant_Combat/Animation",
			"MySpaceShooterTp1/Variant_Combat/Gameplay",
			"MySpaceShooterTp1/Variant_Combat/Interfaces",
			"MySpaceShooterTp1/Variant_Combat/UI",
			"MySpaceShooterTp1/Variant_SideScrolling",
			"MySpaceShooterTp1/Variant_SideScrolling/AI",
			"MySpaceShooterTp1/Variant_SideScrolling/Gameplay",
			"MySpaceShooterTp1/Variant_SideScrolling/Interfaces",
			"MySpaceShooterTp1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
