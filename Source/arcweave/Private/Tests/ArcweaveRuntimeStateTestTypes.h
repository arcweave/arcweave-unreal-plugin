#pragma once

#include "ArcweaveRuntimeState.h"
#include "ArcweaveSubsystem.h"
#include "GameFramework/SaveGame.h"

#include "ArcweaveRuntimeStateTestTypes.generated.h"

UCLASS()
class UArcweaveRuntimeStateTestSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(SaveGame)
    FArcweaveRuntimeState State;
};

UCLASS()
class UArcweaveRuntimeStateTestListener : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY()
    UArcweaveSubsystem* Subsystem = nullptr;

    FArcweaveRuntimeState StateToRestore;
    FArcweaveRuntimeState CapturedInCallback;
    FArcweaveRuntimeState CaptureAttempt;
    FString CaptureError;
    FString RestoreError;
    int32 RestoreEvents = 0;
    int32 VariableEvents = 0;
    int32 ArcscriptEvents = 0;
    int32 ImportEvents = 0;
    bool bProbeDuringScript = false;
    bool bCaptureDuringScriptSucceeded = true;
    bool bRestoreDuringScriptSucceeded = true;
    bool bCaptureInRestoreCallbackSucceeded = false;

    UFUNCTION()
    void HandleStateRestored()
    {
        ++RestoreEvents;
        FString Error;
        bCaptureInRestoreCallbackSucceeded = Subsystem->CaptureState(CapturedInCallback, Error);
    }

    UFUNCTION()
    void HandleVariablesChanged(const TArray<FArcweaveVariable>& Variables)
    {
        ++VariableEvents;
    }

    UFUNCTION()
    void HandleProjectImported(const FArcweaveProjectData& Project)
    {
        ++ImportEvents;
    }

    UFUNCTION()
    void HandleArcscriptEvent(const FString& EventName)
    {
        ++ArcscriptEvents;
        if (bProbeDuringScript)
        {
            bCaptureDuringScriptSucceeded = Subsystem->CaptureState(CaptureAttempt, CaptureError);
            bRestoreDuringScriptSucceeded = Subsystem->RestoreState(StateToRestore, RestoreError);
        }
    }
};
