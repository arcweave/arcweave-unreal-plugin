#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSubsystem.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveAttributeTypesTest,
    "Arcweave.Project.AttributeTypes",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveAttributeTypesTest::RunTest(const FString& Parameters)
{
    const FString Json = TEXT(R"JSON({
        "name": "Attribute types test",
        "boards": {"board-1": {"name": "Main", "elements": ["el-1"]}},
        "elements": {
            "el-1": {
                "title": "Element",
                "content": "<p>Hello</p>",
                "components": ["component-1"],
                "attributes": ["a-plain", "a-rich", "a-bool", "a-int", "a-float", "a-components", "a-assets", "a-unknown", "a-unknown-ctype"]
            }
        },
        "components": {"component-1": {"name": "Hero", "customId": "hero", "assets": {}, "attributes": []}},
        "variables": {},
        "attributes": {
            "a-plain": {"name": "Plain", "cType": "elements", "cId": "el-1", "value": {"type": "string", "data": "x", "plain": true}},
            "a-rich": {"name": "Rich", "cType": "elements", "cId": "el-1", "value": {"type": "string", "data": "<p>x</p>"}},
            "a-bool": {"name": "Bool", "cType": "elements", "cId": "el-1", "value": {"type": "boolean", "data": true}},
            "a-int": {"name": "Int", "cType": "elements", "cId": "el-1", "value": {"type": "integer", "data": 7}},
            "a-float": {"name": "Float", "cType": "elements", "cId": "el-1", "value": {"type": "float", "data": 1.5}},
            "a-components": {"name": "Components", "cType": "elements", "cId": "el-1", "value": {"type": "component-list", "data": ["component-1"]}},
            "a-assets": {"name": "Assets", "cType": "elements", "cId": "el-1", "value": {"type": "asset-list", "data": []}},
            "a-unknown": {"name": "Unknown", "cType": "elements", "cId": "el-1", "value": {"type": "future-type", "data": "x"}},
            "a-unknown-ctype": {"name": "Unknown owner", "cType": "future-owner", "cId": "el-1", "value": {"type": "integer", "data": 1}}
        }
    })JSON");

    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();
    if (!TestTrue(TEXT("Unknown attribute types do not fail the import"), Subsystem->ParseResponse(Json)))
    {
        return false;
    }

    const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
    if (!TestEqual(TEXT("One board imports"), Project.Boards.Num(), 1)
        || !TestEqual(TEXT("The element imports into the board"), Project.Boards[0].Elements.Num(), 1))
    {
        return false;
    }
    const FArcweaveElementData& Element = Project.Boards[0].Elements[0];
    TestEqual(TEXT("An element lists its component ids"), Element.ComponentIds, TArray<FString>{TEXT("component-1")});
    TestEqual(TEXT("Components are stored by id"), Project.ComponentsMap.Num(), 1);

    const auto FindAttribute = [&Element](const TCHAR* Id) -> const FArcweaveAttributeData*
    {
        return Element.Attributes.FindByPredicate([Id](const FArcweaveAttributeData& Attribute) { return Attribute.Id == Id; });
    };
    const auto TestValueType = [this, &FindAttribute](const TCHAR* Id, const EArcweaveAttributeValueDataType Expected)
    {
        const FArcweaveAttributeData* Attribute = FindAttribute(Id);
        if (TestNotNull(FString(TEXT("Attribute imports: ")) + Id, Attribute))
        {
            TestTrue(FString(TEXT("Value type of ")) + Id, Attribute->Value.Type == Expected);
        }
    };
    TestValueType(TEXT("a-plain"), EArcweaveAttributeValueDataType::String);
    TestValueType(TEXT("a-rich"), EArcweaveAttributeValueDataType::StringRichText);
    TestValueType(TEXT("a-bool"), EArcweaveAttributeValueDataType::Boolean);
    TestValueType(TEXT("a-int"), EArcweaveAttributeValueDataType::Integer);
    TestValueType(TEXT("a-float"), EArcweaveAttributeValueDataType::Float);
    TestValueType(TEXT("a-components"), EArcweaveAttributeValueDataType::ComponentList);
    TestValueType(TEXT("a-assets"), EArcweaveAttributeValueDataType::AssetList);
    TestValueType(TEXT("a-unknown"), EArcweaveAttributeValueDataType::Undefined);

    const FArcweaveAttributeData* Components = FindAttribute(TEXT("a-components"));
    if (Components)
    {
        TestEqual(TEXT("A component list keeps its ids"), Components->Value.ComponentIds, TArray<FString>{TEXT("component-1")});
        TestTrue(TEXT("A component list has data"), Components->Value.bHasData);
    }
    const FArcweaveAttributeData* Int = FindAttribute(TEXT("a-int"));
    if (Int)
    {
        TestEqual(TEXT("An integer keeps its value"), Int->Value.Data, FString(TEXT("7")));
    }
    const FArcweaveAttributeData* Unknown = FindAttribute(TEXT("a-unknown"));
    if (Unknown)
    {
        TestFalse(TEXT("An unknown value type has no data"), Unknown->Value.bHasData);
    }

    const FArcweaveAttributeData* Plain = FindAttribute(TEXT("a-plain"));
    if (Plain)
    {
        TestTrue(TEXT("An element attribute keeps the elements owner type"), Plain->cType == EArcweaveAttributeDataType::Elements);
    }
    const FArcweaveAttributeData* UnknownOwner = FindAttribute(TEXT("a-unknown-ctype"));
    if (UnknownOwner)
    {
        TestTrue(TEXT("An unknown owner type is Undefined"), UnknownOwner->cType == EArcweaveAttributeDataType::Undefined);
    }
    return true;
}

#endif
