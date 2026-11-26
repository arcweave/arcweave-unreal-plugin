#pragma once

// Engine includes
#include "CoreMinimal.h"
#include "UObject/Object.h"

// Generated include
#include "ArcweaveUserSettings.generated.h"

/**
 * The Arcweave API token, shown in Project Settings > Plugins > Arcweave API Token. It is saved for the user only, in
 * Saved/Arcweave/APIToken.txt. This object has no config, so editing it never touches the project config files.
 */
UCLASS(Transient)
class ARCWEAVE_API UArcweaveUserSettings : public UObject
{
    GENERATED_BODY()

public:
    /*
     * API key of your Arcweave workspace. Saved in Saved/Arcweave/APIToken.txt, never in Config/DefaultGame.ini.
     * The ARCWEAVE_API_KEY environment variable overrides it.
     */
    UPROPERTY(
        Transient,
        EditAnywhere,
        meta = (
            DisplayName = "API Token",
            PasswordField = true,
            ToolTip = "API key of your Arcweave workspace. Saved in Saved/Arcweave/APIToken.txt, never in Config/DefaultGame.ini. The ARCWEAVE_API_KEY environment variable overrides it."
            ),
        Category = "ArcweaveSettings"
    )
    FString APIToken = FString("");

    virtual void PostInitProperties() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
