# Arcweave Unreal plugin v3.0.0

Arcweave Unreal plugin v3.0.0 adds multi-language projects, reworks how attributes and components are stored, and makes
showing a choice label free of side effects. **It has breaking changes:** read
[Breaking changes / upgrading](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#breaking-changes--upgrading)
before you upgrade from v2.2.0.

## Breaking changes

C++ code that uses the old members won't compile, and Blueprints that use the old pins show broken nodes until they are
updated ([#31](https://github.com/arcweave/arcweave-unreal-plugin/pull/31)):

- `FArcweaveElementData::Components` (copies of the components) is now `ComponentIds`. Resolve each id with
  `TryGetArcweaveComponentById`.
- `FArcweaveProjectData::Components` is now `ComponentsMap`, keyed by component id.
- `FArcweaveAttributeData::cType` and `FArcweaveAttributeValueData::Type` are now the enums `EArcweaveAttributeDataType`
  and `EArcweaveAttributeValueDataType`. Rich text is reported as `StringRichText`.

Behaviour changes that a game may rely on:

- **Showing a choice label no longer applies its Arcscript.** `TranspileConnectionLabel` and `TranspileConnection` used
  to apply the label's assignments and events, such as `resetVisits()`, every time the label was shown. Now they only
  return the text. Call `UpdateVariablesFromConnection` with the connection the player picks to apply its effects. A game
  that only rendered labels and never called it will no longer change variables when an option is chosen. Checking branch
  conditions (`TranspileCondition`, `GetIsTargetBranch`) no longer changes variables or visits either
  ([#46](https://github.com/arcweave/arcweave-unreal-plugin/pull/46)).
- **`visits()` in a label counts the visits of the element the connection starts from** when the label is applied. It
  used to count the visits of the connection itself, which were always 0
  ([#46](https://github.com/arcweave/arcweave-unreal-plugin/pull/46)).
- **The starting element is validated on import.** See [Starting element](#starting-element).
- **The default `Locale` setting is now `en`** (it was `fr`), and the language settings are now saved with the project
  settings. Check them after upgrading if you use `Use Locale`.
- **Unreal Engine 5.5 or later is supported.** Earlier READMEs said 5.0, but the plugin already needed 5.4 to build.

## Localization

Projects with several languages can be imported and switched at runtime
([#24](https://github.com/arcweave/arcweave-unreal-plugin/pull/24)). See
[Localization](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#localization).

- Choose the language to import with the **Use Locale**, **Locale** and **Fallback To Default Locale** settings, or with
  `SaveArcweaveLanguageSettings`. The locale is matched ignoring case; an unknown one logs a warning and imports the main
  language.
- Import a JSON export made with **All languages** to get every language. `HasLocales()` tells you whether the imported
  project has more than one.
- `UpdateContentsWithLocale` switches element titles and contents, connection labels, jumper targets and component names
  to another language without changing the settings, and broadcasts `OnArcweaveLanguageChanged`.
- Missing translations follow each language's **Translates from** chain (the locale's `base`) down to the main language.
  Empty paragraphs count as missing, translations from unrelated languages are never used, and loops of bases are
  detected.
- API imports request a single language, with `fallbackContents=true` when the fallback setting is on.

## Starting element

- An export whose starting element is missing, unknown or not on an imported board (for example an export of selected
  boards) still imports, with an empty `StartingElementId` and a warning that names the id. The Unity and Godot plugins
  behave the same way.
- Passing that empty id to `TranspileObject` fails with an error that says the project has no valid starting element,
  instead of a generic "cannot find transpile data" error.
- Runtime save/load (`CaptureState`/`RestoreState`) is unchanged from v2.2.0. The
  [runtime save/load guide](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/docs/runtime-state.md) now
  reflects that rendering a label doesn't change state.

## API token

- The API token is no longer written to the log. Importing used to log it at Warning level. The settings read on import
  are now logged at `Verbose` under `LogArcwarePlugin`, and the token only as `set` or `empty`
  ([#46](https://github.com/arcweave/arcweave-unreal-plugin/pull/46)).
- **Check your `Config/DefaultGame.ini`.** A token entered in the Arcweave settings is saved there, and that file is
  usually committed to version control and packaged with the game. Clear it before you commit or package. See
  [Web API](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#web-api).

## Other changes

- The folder of the local JSON export can be set with `JsonDirectoryPath` in the Arcweave settings
  ([#30](https://github.com/arcweave/arcweave-unreal-plugin/pull/30)). The README has a new
  [Packaging](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#packaging) section on staging it.
- Plain-text connection labels no longer log a `ParseErrorException`
  ([#42](https://github.com/arcweave/arcweave-unreal-plugin/pull/42)).
- Unreal Engine 5.8 compatibility ([#41](https://github.com/arcweave/arcweave-unreal-plugin/pull/41)).
- Each release now has an `ArcweaveForUnreal.zip` package to extract into `Plugins`
  ([#45](https://github.com/arcweave/arcweave-unreal-plugin/pull/45)).
- The plugin descriptor links to the [documentation](https://docs.arcweave.com/integrations/unreal) and to
  [GitHub issues](https://github.com/arcweave/arcweave-unreal-plugin/issues) for support.

## Installation

Download **ArcweaveForUnreal.zip** below and extract it into your project's `Plugins` folder, so that the plugin ends up in
`Plugins/Arcweave`. When upgrading, delete the previous copy first. Rebuild the project when prompted.

**Full changelog:** https://github.com/arcweave/arcweave-unreal-plugin/compare/v2.2.0...v3.0.0
