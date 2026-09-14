#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSubsystem.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/AutomationTest.h"
#include "Misc/EngineVersionComparison.h"

namespace
{
class FImportTestResponse : public IHttpResponse
{
public:
    int32 Code = 200;
    FString Body;
    FString URL = TEXT("https://arcweave.com/api/test/unreal");
    TArray<uint8> Bytes;
#if UE_VERSION_OLDER_THAN(5, 6, 0)
    virtual FString GetURL() const override { return URL; }
#else
    virtual const FString& GetURL() const override { return URL; }
#endif
    virtual const FString& GetEffectiveURL() const override { return URL; }
    virtual EHttpRequestStatus::Type GetStatus() const override { return EHttpRequestStatus::Succeeded; }
    virtual EHttpFailureReason GetFailureReason() const override { return EHttpFailureReason::None; }
    virtual FString GetURLParameter(const FString&) const override { return {}; }
    virtual FString GetHeader(const FString&) const override { return {}; }
    virtual TArray<FString> GetAllHeaders() const override { return {}; }
    virtual FString GetContentType() const override { return TEXT("application/json"); }
    virtual uint64 GetContentLength() const override { return Bytes.Num(); }
    virtual const TArray<uint8>& GetContent() const override { return Bytes; }
    virtual int32 GetResponseCode() const override { return Code; }
    virtual FString GetContentAsString() const override { return Body; }
#if !UE_VERSION_OLDER_THAN(5, 6, 0)
    virtual FUtf8StringView GetContentAsUtf8StringView() const override { return {}; }
#endif
};
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FArcweaveImportFailuresTest, "Arcweave.Project.ImportFailures",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveImportFailuresTest::RunTest(const FString& Parameters)
{
    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();
    Subsystem->ProjectData.Name = TEXT("Working project");
    AddExpectedError(TEXT("Failed to parse the HTTP Response"), EAutomationExpectedErrorFlags::Contains, 1);
    TestFalse(TEXT("Malformed JSON is rejected"), Subsystem->ParseResponse(TEXT("not JSON")));
    TestFalse(TEXT("An incomplete export is rejected"), Subsystem->ParseResponse(TEXT("{\"name\":\"Incomplete\"}")));
    TestEqual(TEXT("Invalid imports preserve the loaded project"), Subsystem->ProjectData.Name, FString(TEXT("Working project")));

    const auto Response = MakeShared<FImportTestResponse, ESPMode::ThreadSafe>();
    Response->Body = TEXT("{\"name\":\"New project\",\"boards\":{},\"elements\":{},\"components\":{},\"variables\":{}}");
    const auto OldRequest = FHttpModule::Get().CreateRequest();
    const auto NewRequest = FHttpModule::Get().CreateRequest();
    Subsystem->ActiveFetchRequest = OldRequest;
    Subsystem->CancelFetch();
    Subsystem->ActiveFetchRequest = NewRequest;
    Subsystem->HandleFetch(OldRequest, Response, true);
    TestEqual(TEXT("A late cancelled response cannot replace the project"), Subsystem->ProjectData.Name, FString(TEXT("Working project")));
    TestTrue(TEXT("The newer request remains active"), Subsystem->ActiveFetchRequest == NewRequest);

    Response->Code = 401;
    Subsystem->HandleFetch(NewRequest, Response, true);
    TestFalse(TEXT("HTTP failure clears the pending request"), Subsystem->ActiveFetchRequest.IsValid());
    TestEqual(TEXT("HTTP failure preserves the loaded project"), Subsystem->ProjectData.Name, FString(TEXT("Working project")));
    Subsystem->ActiveFetchRequest = NewRequest;
    Subsystem->HandleFetch(NewRequest, nullptr, false);
    TestFalse(TEXT("Transport failure clears the pending request"), Subsystem->ActiveFetchRequest.IsValid());
    TestEqual(TEXT("Transport failure preserves the loaded project"), Subsystem->ProjectData.Name, FString(TEXT("Working project")));

    Response->Code = 200;
    Subsystem->ActiveFetchRequest = NewRequest;
    Subsystem->HandleFetch(NewRequest, Response, true);
    TestEqual(TEXT("A successful retry replaces the project"), Subsystem->ProjectData.Name, FString(TEXT("New project")));
    return true;
}
#endif
