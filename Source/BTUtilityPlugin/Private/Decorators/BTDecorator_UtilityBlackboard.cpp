// Copyright 2015 Cameron Angus. All Rights Reserved.

#include "Decorators/BTDecorator_UtilityBlackboard.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"


UBTDecorator_UtilityBlackboard::UBTDecorator_UtilityBlackboard(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{
	NodeName = "Blackboard Utility";

	// accept only float and integer keys
	UtilityValueKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_UtilityBlackboard, UtilityValueKey));
	UtilityValueKey.AddIntFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_UtilityBlackboard, UtilityValueKey));
}

void UBTDecorator_UtilityBlackboard::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UtilityValueKey.ResolveSelectedKey(*GetBlackboardAsset());
}

float UBTDecorator_UtilityBlackboard::CalculateUtilityValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	float Value = 0.0f;

	if (UtilityValueKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass())
	{
		Value = MyBlackboard->GetValue< UBlackboardKeyType_Float >(UtilityValueKey.GetSelectedKeyID());
	}
	else if (UtilityValueKey.SelectedKeyType == UBlackboardKeyType_Int::StaticClass())
	{
		Value = (float)MyBlackboard->GetValue< UBlackboardKeyType_Int >(UtilityValueKey.GetSelectedKeyID());
	}

	return FMath::Max(Value, 0.0f);
}

FString UBTDecorator_UtilityBlackboard::GetStaticDescription() const
{
	return FString::Printf(TEXT("Utility Key: %s"), *GetSelectedBlackboardKey().ToString());
}

void UBTDecorator_UtilityBlackboard::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FString DescKeyValue;

	if (BlackboardComp)
	{
		DescKeyValue = BlackboardComp->DescribeKeyValue(UtilityValueKey.GetSelectedKeyID(), EBlackboardDescription::OnlyValue);
	}

	Values.Add(FString::Printf(TEXT("utility: %s"), *DescKeyValue));
}


