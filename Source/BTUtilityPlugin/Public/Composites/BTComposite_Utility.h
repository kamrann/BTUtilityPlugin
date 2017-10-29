// Copyright 2015 Cameron Angus. All Rights Reserved.
#pragma once

#include "BehaviorTree/BTCompositeNode.h"
#include "BTUtilityTypes.h"
#include "BTComposite_Utility.generated.h"


UENUM()
enum class EUtilitySelectionMethod: uint8
{
	// The child with the highest utility value is always chosen
	Priority,

	// Selection probability is proportional to utility value
	Proportional,
};

struct FBTUtilityMemory : public FBTCompositeMemory
{
	/** ordering of child nodes for the current search activation (array is a list of child indexes arranged in execution order) */
	FUtilityExecutionOrdering ExecutionOrdering;
};


class FBTUtilityFunctionAccessor;

/** 
 * Utility selector node.
 * Utility Nodes choose at most one of their children to execute. The choice made is a function of the utility values of the children.
 * A Utility Node will succeed if its chosen child succeeds, and will fail if its chosen child fails or if no child could be executed.
 */
UCLASS()
class BTUTILITYPLUGIN_API UBTComposite_Utility: public UBTCompositeNode
{
	GENERATED_BODY()

public:
	// Method used to determine child selection based on utility values
	UPROPERTY(EditAnywhere, Category = "Utility")
	EUtilitySelectionMethod SelectionMethod;

public:
	UBTComposite_Utility();

public:
	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;

protected:
	/**
	Attempt to find a utility function attached to the specified child.
	@return The utility function accessor, or no value if no utility function was found.
	*/
	TOptional< FBTUtilityFunctionAccessor > FindChildUtilityFunction(int32 ChildIndex) const;

	/**
	Attempts to find a utility function attached to the specified child, then invoke its utility calculation.
	@return The calculated utility value, or no value on failure.
	*/
	TOptional< float > EvaluateChildUtility(int32 ChildIndex, FBehaviorTreeSearchData& SearchData) const;

	/**
	Invoke utility function for each child and store all the utility values.
	@return true if at least one utility value is non-zero.
	*/
	bool EvaluateUtilityScores(FBehaviorTreeSearchData& SearchData, TArray< float >& OutScores) const;

protected:
	virtual void NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const override;

public:
	int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif
};

//////////////////////////////////////////////////////////////////////////
// Inlines



