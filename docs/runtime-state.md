# Runtime save/load in C++

`UArcweaveSubsystem::CaptureState` captures Arcweave's mutable runtime state. `RestoreState` validates and restores that state after the same project has been imported. Your game owns save slots, files, the narrative cursor, and world progress.

## Snapshot contents and compatibility

`FArcweaveRuntimeState`, declared in `ArcweaveRuntimeState.h`, contains:

| Field | Contents |
| --- | --- |
| `FormatVersion` | Snapshot format version, currently `1`. |
| `ProjectFingerprint` | Content fingerprint of the imported project. |
| `Variables` | Global, board, and component variables keyed by stable variable or attribute ID. Each `FArcweaveSavedVariable` stores its `Type` and current `Value`. |
| `Visits` | Visit counts keyed by project object ID: elements, connections, branches, conditions, and jumpers. |

The snapshot structs expose reflected `SaveGame` fields and can also be used in Blueprints. Capture does not copy authored defaults or project metadata into the save. Restore preserves those values from the imported project, so Arcscript `reset` and `resetAll` still use the project's authored defaults.

Restore accepts only the same imported project content. The fingerprint uses canonical parsed JSON: object-key order, JSON whitespace, and the API's outer `project` envelope do not affect it. Content changes do affect it, even if the project hash or variable IDs are unchanged. There is no automatic migration between different content versions. Keep the matching export available for saved games; fetching the latest API export can make an older save incompatible.

Both calls return `bool` and provide an `FString` error on failure:

```cpp
bool CaptureState(FArcweaveRuntimeState& State, FString& Error) const;
bool RestoreState(const FArcweaveRuntimeState& State, FString& Error);
```

Call them on the game thread after a successful import and between completed script calls. They reject calls before import, while an API request is in flight, or while Arcscript is executing. Failed capture leaves its output unchanged. Failed restore leaves the live project unchanged and emits no restoration event.

Successful restore applies the complete snapshot before broadcasting `OnArcweaveStateRestored`. It does not emit ordinary variable-change or Arcscript events. Treat this delegate as a state-refresh notification; do not depend on earlier gameplay events being replayed.

## A game-owned save object

The following header and source are an example for your game's module, not additional plugin files. Replace `YOURGAME_API` with your module's export macro and add `"arcweave"` to `PublicDependencyModuleNames` in your game's `.Build.cs`, alongside its existing `Core`, `CoreUObject`, and `Engine` dependencies.

The sample saves resolved dialogue text and choices alongside a cursor. These fields illustrate game-owned presentation state; adapt them to your runner. Add your own inventory, quests, world state, localization, and other progress as needed. The plugin does not infer or persist them.

`NarrativeSaveGame.h`:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ArcweaveRuntimeState.h"
#include "NarrativeSaveGame.generated.h"

USTRUCT()
struct FSavedNarrativeChoice
{
    GENERATED_BODY()

    UPROPERTY(SaveGame)
    FString ConnectionId;

    UPROPERTY(SaveGame)
    FString Label;
};

USTRUCT()
struct FNarrativePresentation
{
    GENERATED_BODY()

    UPROPERTY(SaveGame)
    FString CurrentElementId;

    UPROPERTY(SaveGame)
    FString DisplayText;

    UPROPERTY(SaveGame)
    TArray<FSavedNarrativeChoice> Choices;
};

UCLASS()
class YOURGAME_API UNarrativeSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(SaveGame)
    FArcweaveRuntimeState ArcweaveState;

    UPROPERTY(SaveGame)
    FNarrativePresentation Presentation;
};

bool SaveNarrativeCheckpoint(
    const FString& SlotName,
    int32 UserIndex,
    const FNarrativePresentation& Presentation,
    FString& Error);

bool LoadNarrativeCheckpoint(
    const FString& SlotName,
    int32 UserIndex,
    FNarrativePresentation& OutPresentation,
    FString& Error);
```

`NarrativeSaveGame.cpp`:

```cpp
#include "NarrativeSaveGame.h"

#include "ArcweaveSubsystem.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

bool SaveNarrativeCheckpoint(
    const FString& SlotName,
    int32 UserIndex,
    const FNarrativePresentation& Presentation,
    FString& Error)
{
    Error.Reset();
    UArcweaveSubsystem* Arcweave =
        GEngine->GetEngineSubsystem<UArcweaveSubsystem>();
    UNarrativeSaveGame* Save = Cast<UNarrativeSaveGame>(
        UGameplayStatics::CreateSaveGameObject(UNarrativeSaveGame::StaticClass()));

    if (!Arcweave->CaptureState(Save->ArcweaveState, Error))
    {
        return false;
    }

    Save->Presentation = Presentation;
    if (!UGameplayStatics::SaveGameToSlot(Save, SlotName, UserIndex))
    {
        Error = TEXT("Could not write the narrative save slot.");
        return false;
    }

    return true;
}

bool LoadNarrativeCheckpoint(
    const FString& SlotName,
    int32 UserIndex,
    FNarrativePresentation& OutPresentation,
    FString& Error)
{
    Error.Reset();
    UNarrativeSaveGame* Save = Cast<UNarrativeSaveGame>(
        UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    if (!Save)
    {
        Error = TEXT("Could not load a narrative save from this slot.");
        return false;
    }

    UArcweaveSubsystem* Arcweave =
        GEngine->GetEngineSubsystem<UArcweaveSubsystem>();
    if (!Arcweave->RestoreState(Save->ArcweaveState, Error))
    {
        return false;
    }

    OutPresentation = Save->Presentation;
    return true;
}
```

These synchronous helpers assume gameplay has initialized the engine and enabled the Arcweave plugin. `UArcweaveSubsystem` is an **engine subsystem**, so use `GEngine->GetEngineSubsystem<UArcweaveSubsystem>()`. It is not a game-instance subsystem and is shared at the engine level.

Surface the returned error in your load/save UI. The load helper changes `OutPresentation` only after successful restore. When extending the save with game-specific data, validate that data before restoring Arcweave and applying the rest of your checkpoint.

## Import, restore, then resume

1. Pause your narrative runner and choose the project export associated with the save. Mark the operation as a pending load before starting the import.
2. For local data, call `LoadJsonFile()` and check its result. For an API import, bind `OnArcweaveResponseReceived` and `OnArcweaveFetchCompleted` before calling `FetchData` or `FetchDataFromAPI`. Wait for a successful import before calling the load helper; `RestoreState` does not import the project itself.
3. In your successful-import handler, branch on the pending-load flag. For a load, call `LoadNarrativeCheckpoint`, apply the returned presentation and your game's saved world state, and resume only after all steps succeed. Start the initial element only for a new game. Do not automatically execute it on every `OnArcweaveResponseReceived` event.
4. Handle an unsuccessful API completion or failed restore by reporting the error and keeping the runner paused. A failed import keeps the previously loaded project, but that does not mean the requested save has been restored. Cancelled imports do not emit a completion event; handle cancellation in your own load flow.

`OnArcweaveStateRestored` fires inside `RestoreState`, before the example load helper copies `OutPresentation`. Resume from the load helper's successful return, after your game-owned checkpoint is ready, rather than resuming inside that delegate.

Save at a stable checkpoint after element execution, connection-label evaluation, and any related gameplay effects have completed. Keep the saved cursor and presentation consistent with the captured variables and visits.

Do not call `TranspileObject` or `TranspileConnectionLabel` again just to redraw a restored screen: those calls execute Arcscript and can change variables, visits, or other results. Display the resolved text and choices from your checkpoint, then let the next player action continue through your runner. If your game uses a different checkpoint boundary, define explicitly which operation executes next and persist enough information to avoid replaying an already completed operation.

## Verification

Build a Development Editor target with the plugin enabled. Open Unreal Editor's **Automation** window (**Tools > Test Automation** in newer versions, or the **Automation** tab in **Session Frontend**), find `Arcweave.Project.RuntimeState`, and run it.

For a command-line run on Windows, replace the executable and project paths:

```powershell
& "C:\Path\To\UE\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" `
    "C:\Path\To\YourGame\YourGame.uproject" `
    -unattended -nop4 -NullRHI `
    '-ExecCmds=Automation RunTests Arcweave.Project.RuntimeState' `
    '-TestExit=Automation Test Queue Empty' `
    -log
```

This automation test verifies the plugin's runtime-state behavior. Also exercise your game's complete import/save/load/resume path, including presentation and world state; those are outside the plugin snapshot.
