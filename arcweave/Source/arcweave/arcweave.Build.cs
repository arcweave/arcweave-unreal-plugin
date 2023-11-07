// Copyright Epic Games, Inc. All Rights Reserved.
using System;
using System.IO;
using UnrealBuildTool;

public class arcweave : ModuleRules
{
	public arcweave(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		// for windows only? check this afterwards?
		bUseRTTI = true;
		// we are using exceptions so we have to enable that
		bEnableExceptions = true;
		PublicAdditionalLibraries.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ArcscriptTranspiler", "x64", "Release", "ArcscriptTranspiler.lib"));
		//PublicDelayLoadDLLs.Add("ArcscriptTranspiler.dll");
		RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/ArcscriptTranspiler/x64/Release/ArcscriptTranspiler.dll");
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"ArcscriptTranspiler",
				"Projects",
				"Json",
				"JsonUtilities", 
				"Engine",
				"HTTP"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"Settings" 
			});
	}
}
