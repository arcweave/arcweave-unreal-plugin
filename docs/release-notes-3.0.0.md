# Arcweave Unreal plugin v3.0.0

Arcweave Unreal plugin v3.0.0 adds multi-language projects, reworks how attributes and components are stored, shows option texts like
play mode and makes showing a choice label free of side effects. **It has breaking changes:** read
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
- **Connections without label text now have an option text** (see [Option texts](#option-texts)). A game that hid
  options whose `TranspileConnectionLabel` was empty now shows them; it still gets an empty text for an option whose
  conditions don't hold.
- **The starting element is validated on import.** See [Starting element](#starting-element).
- **The API token is saved per user**, not in `Config/DefaultGame.ini`. See [API token](#api-token).
- **The default `Locale` setting is now `en`** (it was `fr`), and the language settings are now saved with the project
  settings. Check them after upgrading if you use `Use Locale`.
- **Unreal Engine 5.5 or later is supported.** Earlier READMEs said 5.0, but the plugin already needed 5.4 to build.

## Localization

Projects with several languages can be imported and switched at runtime
([#24](https://github.com/arcweave/arcweave-unreal-plugin/pull/24)). See
[Localization](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#localization).

- Choose the language to import with the **Use Locale**, **Locale** and **Fallback To Default Locale** settings, or with
  `SaveArcweaveLanguageSettings`.
- Import an **Export as JSON** made with **All languages** to get every language; **Export for Unreal** contains a single
  language. With an **All languages** JSON export the locale is matched ignoring case, and an unknown one logs a warning and imports the
  main language. `HasLocales()` tells you whether the imported project has more than one language.
- `UpdateContentsWithLocale` switches element titles and contents, connection labels, jumper targets and component names
  to another language without changing the settings, and broadcasts `OnArcweaveLanguageChanged`.
- Missing translations follow each language's **Translates from** chain (the locale's `base`) down to the main language.
  Empty paragraphs count as missing, translations from unrelated languages are never used, and loops of bases are
  detected.
- API imports request a single language, with `fallbackContents=true` when the fallback setting is on. The API matches
  the locale code exactly, including its case (`FR` is not `fr`), and doesn't fall back to the main language for a code
  the project doesn't have. The API then either returns empty texts and the import succeeds, or rejects the code with
  HTTP 400, so the import fails, `OnArcweaveFetchCompleted` reports it and the previous project is kept. In both cases,
  check the code's spelling and case. With **Use Locale** on, set `Locale` to `*` to import all languages through the
  API, or to `__default__` for the main language.

## Starting element

- An export whose starting element is missing, unknown or not on an imported board (for example an export of selected
  boards) still imports, with an empty `StartingElementId` and a warning that says why, naming the id when there is one.
  Like the Unity plugin, the import doesn't fail because of the starting element.
- Passing that empty id to `TranspileObject` fails with an error that says the project has no valid starting element,
  instead of a generic "cannot find transpile data" error.
- Runtime save/load (`CaptureState`/`RestoreState`) is unchanged from v2.2.0. The
  [runtime save/load guide](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/docs/runtime-state.md) now
  reflects that rendering a label doesn't change state.

## Option texts

`TranspileConnectionLabel` now falls back like Arcweave's play mode when a connection's label has no text
([#48](https://github.com/arcweave/arcweave-unreal-plugin/pull/48)). See
[Option texts](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#option-texts).

- The text comes from a later label with text, else the title of the element the connection leads to, else the first
  paragraph of its content cut to 70 characters, else `[ Empty element ]`. It used to be empty. Labels with text are
  returned as before.
- It returns an empty string, so the option shouldn't be shown, when no branch condition on the path holds or a label or
  condition script on the path fails to run. Blank branch conditions are skipped.
- New `HasOptions(Element, BoardData)` is false when the element has no choice to show.
- Titles and option texts are plain text: entities such as `&amp;` are decoded, mentions show their text and code is
  removed.
- A failing Arcscript no longer leaks memory in the Arcscript wrapper.

## API token

- The plugin no longer writes the API token to its log. Importing used to log it at Warning level. The settings read on import
  are now logged at `Verbose` under `LogArcwarePlugin`, and the token only as `set` or `empty`
  ([#46](https://github.com/arcweave/arcweave-unreal-plugin/pull/46)).
- **The token is saved per user.** It is stored in `Saved/Arcweave/APIToken.txt` (owner-only on macOS) instead of `Config/DefaultGame.ini`, so
  it is no longer committed with the project or packaged with the game. The `ARCWEAVE_API_KEY` environment variable
  overrides it. The first time you open the project in the editor, a token that an earlier version saved is copied to
  your user file. The plugin doesn't edit `DefaultGame.ini`: while it contains a token, the editor warns and a cook
  commandlet fails with an error (cooking in the editor, such as Quick Launch, only gets the warning). **Remove the
  `APIToken` lines from it, and if it was committed or a build made with it was shared, revoke that token in your
  Arcweave workspace and create a new one.** The token is entered on its own settings page, **Arcweave API Token**. Unreal's HTTP module can log request headers, including the token, at `Verbose` or
  `VeryVerbose`. See
  [Where the token is saved](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#where-the-token-is-saved).
- A packaged game no longer gets the token from the project config: a game that fetches from the API at runtime must
  pass its own token to `FetchData`, save it with `SaveArcweaveSettings`, or set `ARCWEAVE_API_KEY`. `FetchData` with an empty token uses `ARCWEAVE_API_KEY` or the saved token.

## Other changes

- The plugin no longer rewrites `Config/DefaultGame.ini` every time the editor starts, and entering the API token in
  the settings doesn't change that file.
- The folder of the local JSON export can be set with `JsonDirectoryPath` in the Arcweave settings
  ([#30](https://github.com/arcweave/arcweave-unreal-plugin/pull/30)). The README has a new
  [Packaging](https://github.com/arcweave/arcweave-unreal-plugin/blob/v3.0.0/README.md#packaging) section on staging it.
- The prebuilt Arcscript libraries support Windows (Win64) and macOS on Apple Silicon (arm64).
- String variables assigned non-ASCII text in Arcscript (e.g. `name = "Café"`) keep their characters.
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
