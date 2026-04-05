using System.IO;
using UnrealBuildTool;
public class ArcscriptTranspiler : ModuleRules
{
    public ArcscriptTranspiler(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Add the import library
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "ArcscriptTranspiler.lib"));
            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add("ArcscriptTranspiler.dll");
            // Ensure that the DLL is staged along with the executable
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/ArcscriptTranspiler/lib/ArcscriptTranspiler.dll");
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/ArcscriptTranspiler/lib/antlr4-runtime.dll");

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            // Absolute path to the dynamic library that ships with the plugin
            string DylibPath = Path.Combine(ModuleDirectory, "lib", "libArcscriptTranspiler.dylib");
            string Antlr4DylibPath = Path.Combine(ModuleDirectory, "lib", "libantlr4-runtime.dylib");

            // On macOS the linker still needs to see the library which provides the
            // symbols referenced from the headers (e.g. runScriptExport). Therefore
            // we add the dylib to the list of libraries to link against.
            PublicAdditionalLibraries.Add(DylibPath);

            // Stage the dylibs to the plugin's Binaries/Mac folder, which is the
            // standard UE location for plugin binaries and where arcweave.cpp loads
            // them from at runtime. The single-argument form of RuntimeDependencies
            // would copy to the wrong location in packaged builds.
            string OutputDir = Path.Combine(PluginDirectory, "Binaries", "Mac");
            RuntimeDependencies.Add(Path.Combine(OutputDir, "libArcscriptTranspiler.dylib"), DylibPath);
            RuntimeDependencies.Add(Path.Combine(OutputDir, "libantlr4-runtime.dylib"), Antlr4DylibPath);

            // Also stage to the target output directory for packaged game builds.
            RuntimeDependencies.Add("$(BinaryOutputDir)/libArcscriptTranspiler.dylib", DylibPath);
            RuntimeDependencies.Add("$(BinaryOutputDir)/libantlr4-runtime.dylib", Antlr4DylibPath);
        }

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Public")
        });
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "Projects",
            "CoreUObject",
            "Json",
            "JsonUtilities",
            "Engine",
            "DeveloperSettings"
        });
    }
}
