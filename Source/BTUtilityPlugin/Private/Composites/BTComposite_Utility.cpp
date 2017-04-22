// Copyright 2015 Cameron Angus. All Rights Reserved.

#include "Composites/BTComposite_Utility.h"
#include "Decorators/BTDecorator_UtilityFunction.h"
#include "UtilitySelectionMethods/BTUtilitySelectionMethod_Highest.h"
#include "UtilitySelectionMethods/BTUtilitySelectionMethod_Proportional.h"


UBTComposite_Utility::UBTComposite_Utility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Utility";
	bUseNodeActivationNotify = true;

	SelectionMethod = EUtilitySelectionMethod::Priority;

	OnNextChild.BindUObject(this, &UBTComposite_Utility::GetNextChildHandler);
}

void UBTComposite_Utility::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	FBTUtilityMemory* UtilityMemory = reinterpret_cast<FBTUtilityMemory*>(NodeMemory);
	if (InitType == EBTMemoryInit::Initialize)
	{
		// Invoke the constructor for our TArray
		new (&UtilityMemory->ExecutionOrdering) FUtilityExecutionOrdering();
	}
}

FString UBTComposite_Utility::GetStaticDescription() const
{
	switch (SelectionMethod)
	{
	case EUtilitySelectionMethod::Priority:
		return TEXT("Priority selection");

	case EUtilitySelectionMethod::Proportional:
		return TEXT("Proportional selection");

	default:
		check(false);
		return{};
	}
}

const UBTDecorator_UtilityFunction* UBTComposite_Utility::FindChildUtilityFunction(int32 ChildIndex) const
{
	auto const& ChildInfo = Children[ChildIndex];
	for (auto Dec : ChildInfo.Decorators)
	{
		auto AsUtilFunc = Cast< UBTDecorator_UtilityFunction >(Dec);
		if (AsUtilFunc)
		{
			// Take the first one. Multiple utility function decorators on a single node is a user
			// error, and generates a warning in the behavior tree editor.
			return AsUtilFunc;
		}
	}

	// Child does not have a utility function decorator
	return nullptr;
}

#if 0
bool UBTComposite_Utility::ShouldConsiderChild(UBehaviorTreeComponent& OwnerComp, int32 InstanceIdx, int32 ChildIdx) const
{
	auto UtilityFunc = Children[ChildIdx].UtilityFunction;

	switch (UtilityFunc->DecoratorPolicy)
	{
	case EUtilityChildConsiderationPolicy::IgnoreIfCantRun:
		/*
		@TODO: Is there any performance or correctness issue here?
		We are doing a decorator check, which will then be repeated for the selected child node (and really
		should give the same result)
		*/
		return DoDecoratorsAllowExecution(OwnerComp, InstanceIdx, ChildIdx);

	default:
		return true;
	}
}
#endif

bool UBTComposite_Utility::EvaluateUtilityScores(FBehaviorTreeSearchData& SearchData, TArray< float >& OutScores) const
{
	bool bIsNonZeroScore = false;
	// Loop through utility children
	for(int32 Idx = 0; Idx < GetChildrenNum(); ++Idx)
	{
		auto UtilityFunc = FindChildUtilityFunction(Idx);
		
		// Calculate utility value
		auto Score = UtilityFunc ?
			UtilityFunc->WrappedCalculateUtility(SearchData.OwnerComp, UtilityFunc->GetNodeMemory< uint8 >(SearchData)) :
			0.0f;

		OutScores.Add(Score);
		bIsNonZeroScore = bIsNonZeroScore || Score > 0.0f;
	}

	return bIsNonZeroScore;
}

void UBTComposite_Utility::NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const
{
	FBTUtilityMemory* NodeMemory = GetNodeMemory<FBTUtilityMemory>(SearchData);

	// Evaluate utility scores for each child
	TArray< float > UtilityValues;
	bool bNonZeroUtility = EvaluateUtilityScores(SearchData, UtilityValues);

	// Generate ordering
	switch (SelectionMethod)
	{
	case EUtilitySelectionMethod::Priority:
		UtilitySelection::PriorityOrdering(UtilityValues, NodeMemory->ExecutionOrdering);
		break;
	case EUtilitySelectionMethod::Proportional:
		UtilitySelection::ProportionalOrdering(UtilityValues, NodeMemory->ExecutionOrdering);
		break;
	default:
		check(false);
	}
}

int32 UBTComposite_Utility::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	FBTUtilityMemory* NodeMemory = GetNodeMemory<FBTUtilityMemory>(SearchData);

	// success = quit
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	check(NodeMemory->ExecutionOrdering.Num() == GetChildrenNum());
	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		// newly activated: start from first in the ordering
		NextChildIdx = NodeMemory->ExecutionOrdering[0];
	}
	else if (LastResult == EBTNodeResult::Failed)
	{
		// @NOTE: Linear search to find position in ordering of last executed child. This could be avoided but overhead is negligible
		// so seems better to avoid storing extra state in the node memory.
		int32 OrderingIndex = NodeMemory->ExecutionOrdering.IndexOfByKey(PrevChild) + 1;
		if (OrderingIndex < NodeMemory->ExecutionOrdering.Num())
		{
			// failed = choose next child in the ordering
			NextChildIdx = NodeMemory->ExecutionOrdering[OrderingIndex];
		}
	}

	return NextChildIdx;
}

uint16 UBTComposite_Utility::GetInstanceMemorySize() const
{
	return sizeof(FBTUtilityMemory);
}

#if WITH_EDITOR

FName UBTComposite_Utility::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Composite.Utility.Icon");
}

#endif


