// Copyright 2015 Cameron Angus. All Rights Reserved.

#pragma once

#include "Decorators/BTDecorator_UtilityFunction.h"
#include "BTDecorator_UtilityBlackboard.generated.h"


class UBehaviorTree;

/**
* Blackboard based utility function.
* The associated node's utility value is specified via a blackboard key.
* The key must be of type Float or Integer.
*/
UCLASS(Meta = (DisplayName = "Blackboard Utility", Category = "Utility Functions"))
class BTUTILITYPLUGIN_API UBTDecorator_UtilityBlackboard : public UBTDecorator_UtilityFunction
{
	GENERATED_UCLASS_BODY()

	/** initialize any asset related data */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual FString GetStaticDescription() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

	/** get name of selected blackboard key */
	FName GetSelectedBlackboardKey() const;

protected:
	/** blackboard key selector */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector UtilityValueKey;

protected:
	virtual float CalculateUtilityValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

//////////////////////////////////////////////////////////////////////////
// Inlines

FORCEINLINE FName UBTDecorator_UtilityBlackboard::GetSelectedBlackboardKey() const
{
	return UtilityValueKey.SelectedKeyName;
}
