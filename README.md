# Arcweave Plugin for Unreal Engine

This is the official README file for the Arcweave plugin repository, which facilitates the importation of [Arcweave](https://arcweave.com/) projects into Unreal Engine (version 5.0 and later). 
The plugin utilizes Arcweave's web API to fetch data, a feature available exclusively to Team account users.

## Plugin Installation

To install the Arcweave Plugin for Unreal Engine, follow these steps:

1. Download the plugin from this repository.
2. Copy the plugin into the **ProjectRootDirectory/Plugins** folder.
3. Open your project.
4. If prompted to rebuild the Arcweave plugin, click **Yes**.

### Arcweave's Web API

This feature is available only to Team account holders. It allows you to fetch your Arcweave project's data directly within Unreal Engine, via Arcweave's web API. You will need:

- Your **API key** as an Arcweave user.
- Your **project's hash**.

Refer to [this chapter](https://arcweave.com/docs/1.0/api) in the Arcweave Documentation for details on how to find these.

### Arcweave's Web API Credentials in Unreal Engine

Navigate to Project Settings -> Plugins -> Arcweave. Here, you can input your APIToken and the project hash obtained in the previous step.

### Fetching the Data

Once the project credentials are correctly set, the Arcweave plugin will automatically fetch the data and populate the UArcweaveSubsystem upon project initialization. Any additional data fetching during runtime must be manually configured. Example usage can be found in the **Demo scene**.

### Important Classes and Functions

The primary class that contains all the blueprint-exposed functions and data is **UArcweaveSubsystem**. This class is located in the file path `Plugins\arcweave\Source\arcweave\Public\ArcweaveSubsystem.h`. 
It provides a range of functions that can be utilized in both Blueprints and C++ to interact with, modify, and retrieve data.

#### List of Important Functions in `UArcweaveSubsystem`:

1. **Fetch Data from Arcweave API**
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

These functions provide a comprehensive set of tools for interacting with the Arcweave API and managing project data within your Unreal Engine project.

## Using the Demo Project

You can explore the plugin implementation and see examples of its usage in our demo project, [Arcweave]([https://arcweave.com/](https://github.com/Arcweave/arcweave-unreal-example)). 
This project includes a demo scene and samples of logic implementation using Arcweave's Web API, showcasing all the capabilities of the plugin.
