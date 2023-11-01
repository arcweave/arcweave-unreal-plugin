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

## Using the Demo Project

You can explore the plugin implementation and see examples of its usage in our demo project, [Arcweave]([https://arcweave.com/](https://github.com/Arcweave/arcweave-unreal-example)). 
This project includes a demo scene and samples of logic implementation using Arcweave's Web API, showcasing all the capabilities of the plugin.
