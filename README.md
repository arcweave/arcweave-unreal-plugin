# Arcweave Plugin for Unreal Engine

[![Version](https://img.shields.io/badge/version-1.1-blue.svg)](https://github.com/arcweave/arcweave-unreal-plugin)
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.0%2B-0E1128?logo=unrealengine)](https://www.unrealengine.com/)
[![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=cplusplus)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![GitHub Issues](https://img.shields.io/github/issues/arcweave/arcweave-unreal-plugin)](https://github.com/arcweave/arcweave-unreal-plugin/issues)
[![Discord](https://img.shields.io/badge/Discord-Join%20Us-7289DA?logo=discord&logoColor=white)](https://discord.gg/kb4FxBxw)
[![YouTube](https://img.shields.io/badge/YouTube-Tutorial%20Series-FF0000?logo=youtube&logoColor=white)](https://www.youtube.com/playlist?list=PLP2s5PcDiBdYRg0zHpJTuiDVf9JF_inyH)

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/Ws_Cz-IQQYg/0.jpg)](https://www.youtube.com/watch?v=Ws_Cz-IQQYg)

This is the official README file for the Arcweave plugin repository, which facilitates the import of [Arcweave](https://arcweave.com/) projects into Unreal Engine (version 5.0 and later). 
The plugin can import data from an exported Arcweave JSON file (available to all Arcweave users) or it can directly utilize Arcweave's web API to fetch data, a feature available to Arcweave Team account owners. You can watch a [full video tutorial series](https://www.youtube.com/playlist?list=PLP2s5PcDiBdYRg0zHpJTuiDVf9JF_inyH) on how to install and use the plugin.

## Table of Contents

- [Plugin Installation](#plugin-installation)
- [Packaging](#packaging) 
- [Data Collection Methods](#data-collection-methods)
   - [JSON Import](#json-import)
   - [Web API](#web-api)
- [Important Classes and Functions](#important-classes-and-functions)
   - [UArcweaveSubsystem Functions](#list-of-important-functions-in-uarcweavesubsystem)
   - [ArcscriptTranspilerWrapper](#arcweave-transpiler-script-wrapper-arcscripttranspilerwrapper)
   - [ArcweaveModule](#plugin-module-arcweavemodule)
   - [Data structs](#data-structs)
- [Using the Demo Project](#using-the-demo-project)
- [Support](#support)

## Plugin Installation

To install the Arcweave Plugin for Unreal Engine, follow these steps:

1. Download the plugin from this repository.
2. Copy the plugin (the downloaded .zip file) into the **ProjectRootDirectory/Plugins** folder. If this folder does not exist please create it.
3. Open your project.
4. If prompted to rebuild the Arcweave plugin, click **Yes**.

## Data Collection Methods
There are two primary methods for collecting Arcweave project data:

### JSON Import: 
For this method, you'll need to do the following: 
- Export your Arcweave project for Unreal Engine and unzip it.
- Move the exported JSON file along with all required assets in the **Content->ArcweaveExport** directory. If this directory does not exist create it.
- ⚠️ Make sure you set the thick to the field "Enable receive method from local JSON" inside Unreal under ProjectSettings at the tab "Arcweave Settings"
  
  <img width="686" height="55" alt="immagine" src="https://github.com/user-attachments/assets/e372638f-e237-4a5b-bd16-09382a8252d1" />

### Web API:
This involves fetching data directly from the Arcweave Web API within Unreal Engine. You will need:

- Your **Arcweave API key** and your **project's hash** (Refer to the [Arcweave Documentation](https://arcweave.com/docs/1.0/api) for more info on how to find these).
- Navigate to Project Settings -> Plugins -> Arcweave. Here, you can input your APIToken and the project hash obtained in the previous step.

## Important Classes and Functions

``` mermaid
   classDiagram
   class UArcweaveSubsystem{}

   class UArcscriptTranspilerWrapper{}
   class FarcweaveModule {}
   class FArcweaveProjectData {}
   UArcweaveSubsystem --|> UEngineSubsystem
   UArcweaveSubsystem *--> FArcweaveProjectData: provides
   UArcweaveSubsystem ..> UArcscriptTranspilerWrapper
   UArcscriptTranspilerWrapper ..> FArcweaveProjectData
   UArcweaveSubsystem ..> FarcweaveModule
   FarcweaveModule *--> UArcscriptTranspilerWrapper
```
The primary class that contains all the blueprint-exposed functions and data is **UArcweaveSubsystem**. This class is located in the file path `Plugins\arcweave\Source\arcweave\Public\ArcweaveSubsystem.h`. 
It provides a range of functions that can be utilized in both Blueprints and C++ to interact with, modify, and retrieve data.

#### List of Important Functions in `UArcweaveSubsystem`:
``` mermaid
   classDiagram
   class UArcweaveSubsystem{
      +HandleApiCall
      +HandleSettings
      +HandleArcweaveProjectData
      +ParseDataFromJson
      +TranspileData
   }

   UArcweaveSubsystem --|> UEngineSubsystem
```
1. **Fetch Data from Arcweave API or local JSON**
   - This function allows you to fetch data from the Arcweave API by providing the API token and project hash.

2. **Load Arcweave API Token from Settings**
   - This function retrieves the Arcweave API token from the settings.

3. **Save Arcweave API Token to Settings**
   - This function saves the Arcweave API token to the settings, using the provided API token and project hash.

4. **Get Arcweave Project Data**
   - This function retrieves the Arcweave project data.

5. **Run Transpiler for the Element and Increase Visits Counter**
   - This function runs the transpiler for a specific element and increases the visits counter for that element. It requires the object ID as an input.

6. **Run Transpiler for the Condition**
   - This function runs the transpiler for a specific condition. It requires the condition ID as an input.

7. **Set Variable**
   - This function lets you modify the current variable value outside the dialogue logic. From anywhere in the project. You only need to provide the variable ID.

These functions provide a comprehensive set of tools for interacting with the Arcweave API and managing project data within your Unreal Engine project.

### Arcweave Transpiler script wrapper `ArcscriptTranspilerWrapper`:
```mermaid

   classDiagram
   class ArcweaveSubsystem{}
   class ArcscriptTranspilerWrapper{
      +RunScript()
      +HandleArcweaveDll()
   }
   ArcweaveSubsystem ..> ArcscriptTranspilerWrapper: run the code throught
```
Run scripts fetched from JSON or through the Web API using Arcweave DLLs from the plugin.

### Plugin module `ArcweaveModule`:
```mermaid

   classDiagram
   class ArcweaveModule{
      + HandlePluginModule()
      + ProvidesHookToReachTranspiler()
   }
   ArcweaveModule ..> ArcscriptTranspilerWrapper: gets
```
This class provides the possibility to access the Arcweave wrapper to call the DLL functions that interpret the code inside the Arcweave app.

```cpp   
         FarcweaveModule* arcweaveModule = FModuleManager::GetModulePtr<FarcweaveModule>("Arcweave");
         UArcscriptTranspilerWrapper* ArcscriptWrapper = arcweaveModule->getArcscriptWrapper();
```
### Data structs:
Wrapper structs containing a series of Blueprint-type structs needed to use the transpiler, and convert the data from and to JSON.

[View Complete relationship between data structs UML Diagram](./Docs/DataDiagramClassUML.md)

#### Project struct :`ArcweaveProjectData`
This is the struct containing the board(ref to the image below) objects, the cover, all the components, and connection present in the project

```mermaid

classDiagram
direction TB

note for FArcweaveProjectData "Main Data Container"
    class FArcweaveProjectData {
	    +FString Name
	    +  Boards
	    +  Variables
	    +  Cover
	    +  ComponentsMap
	    +  Conditions
	    +  Connections
    }

    class FArcweaveBoardData {
	    +FString Id
	    +FString Name
	    + Elements
	    + Connections
	    + Branches
	    + Jumpers
    }

    class FArcweaveVariable {
	    +FString Id
	    +FString Name
	    +FString Type
	    +FString Value
    }

   
	<<USTRUCT>> FArcweaveProjectData
	<<USTRUCT>> FArcweaveBoardData
	<<USTRUCT>> FArcweaveVariable


    FArcweaveProjectData --> FArcweaveBoardData : contains
    FArcweaveProjectData --> FArcweaveVariable : has

```

#### Board struct :`ArcweaveBoardData`
[![ArcweaveBoard image in web app](./Docs/BoardExample.png)](./Docs/BoardExample.png)

The board is the second most important container and represent what we see in the app in the red rectangle looking at the figure


```mermaid
classDiagram
direction TB
    class FArcweaveBoardData {
	    +FString Id
	    +FString Name
	    +TArray\~FArcweaveElementData\~ Elements
	    +TArray\~FArcweaveConnectionsData\~ Connections
	    +TArray\~FArcweaveBranchData\~ Branches
	    +TArray\~FArcweaveJumpersData\~ Jumpers
    }

    class FArcweaveElementData {
	    +FString Id
	    +FString Title
	    +FString Content
	    +TArray\~FArcweaveConnectionsData\~ Outputs
	    +TArray\~FString\~ ComponentIds
	    +TArray\~FArcweaveAttributeData\~ Attributes
    }

    class FArcweaveConnectionsData {
	    +FString Id
	    +FString Label
	    +FString SourceId
	    +FString TargetId
    }

    class FArcweaveBranchData {
	    +FString Id
	    +TArray\~FArcweaveConditionData\~ Conditions
	    +TArray\~FString\~ ConnectionIds
    }

	<<USTRUCT>> FArcweaveBoardData
	<<USTRUCT>> FArcweaveElementData
	<<USTRUCT>> FArcweaveConnectionsData
	<<USTRUCT>> FArcweaveBranchData

    FArcweaveBoardData --> FArcweaveElementData : has
    FArcweaveBoardData --> FArcweaveConnectionsData : connects via
    FArcweaveBoardData --> FArcweaveBranchData : manages
```

## Using the Demo Project

You can explore the plugin implementation and see examples of its usage in our [Arcweave demo project](https://github.com/Arcweave/arcweave-unreal-example). 
This project includes a demo scene and samples of logic implementation using Arcweave's Web API, showcasing all the capabilities of the plugin.

## Support

If you need support for an issue, you can open it using the CONTRIBUTING.md guide on GitHub or you can reach out on the  [🔗 Discord server](https://discord.gg/kb4FxBxw).
.
