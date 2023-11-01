# Arcweave Plugin for Unreal

Official plugin for importing [Arcweave](https://arcweave.com/) projects into Unreal engine (5.0 and later). It uses the Arcweave data fetched via Arcweave's web API (available only to Team users).


## Plugin installation

To install the Arcweave Plugin for Unity:

1. Download the plugin from this repository.
2. Copy the plugin in the **ProjectRootDirectory/Plugins** folder
3. Open your project.
4. If a prompt appears to rebuild the Arcweave plugin, press **Yes**.

### Arcweave's Web API

Feature available to Team account holders only. You can fetch your Arcweave project's data from within Unreal engine, via Arcweave's web API.

To do this, you will need:

* your **API key** as an Arcweave user.
* your **project's hash**.

[This chapter](https://arcweave.com/docs/1.0/api) in the Arcweave Documentation explains where to find both of them.


## Using the Demo Scene

Included in the plugin's package is also a `Demo` folder; a scene recreating Arcweave's Play Mode environment.

### Running the Demo

To see the Unreal Arcweave Player demo scene in action:

 1. Make sure that in the content folder -> Show Plugin content is enabled
 2. Open the **MAP_ArcweaveDemoScene**.
 3. Hit **Play**.
