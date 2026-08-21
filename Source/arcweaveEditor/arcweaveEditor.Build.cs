using UnrealBuildTool;

public class arcweaveEditor : ModuleRules
{
    public arcweaveEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "arcweave",
                "EditorSubsystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "AssetRegistry",
                "Json",
                "JsonUtilities",
                "UnrealEd"
            }
        );
    }
}
