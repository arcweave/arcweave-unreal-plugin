#include "ArcweaveUserSettings.h"

#include "ArcweaveSettings.h"

#if WITH_EDITOR
#include "UObject/UnrealType.h"
#endif

void UArcweaveUserSettings::PostInitProperties()
{
    Super::PostInitProperties();
    APIToken = UArcweaveSettings::GetUserAPIToken();
}

#if WITH_EDITOR
void UArcweaveUserSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UArcweaveUserSettings, APIToken))
    {
        UArcweaveSettings* Settings = GetMutableDefault<UArcweaveSettings>();
        if (Settings == nullptr || !Settings->SetUserAPIToken(APIToken))
        {
            // Show what is actually saved
            APIToken = UArcweaveSettings::GetUserAPIToken();
        }
    }
}
#endif
