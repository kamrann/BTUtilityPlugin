// Copyright 2015 Cameron Angus. All Rights Reserved.

#include "BTUtilityPluginPCH.h"
#include "UtilitySelectionMethods/BTUtilitySelectionMethod_BlueprintBase.h"


UBTUtilitySelectionMethod_BlueprintBase::UBTUtilitySelectionMethod_BlueprintBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
/*	@TODO: Look into this.

	UClass* StopAtClass = UBTService_BlueprintBase::StaticClass();
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		BlueprintNodeHelpers::CollectPropertyData(this, StopAtClass, PropertyData);
	}
	*/
}

void UBTUtilitySelectionMethod_BlueprintBase::GenerateOrdering(TArray< float > const& UtilityValues, FUtilityExecutionOrdering& ExecutionOrdering)
{
	ExecutionOrdering.SetNumUninitialized(UtilityValues.Num());
// @TODO:	GenerateExecutionOrder(UtilityValues, ExecutionOrdering);

	check(ExecutionOrdering.Num() == UtilityValues.Num());
}

FString UBTUtilitySelectionMethod_BlueprintBase::GetDesc()
{
	return GetClass()->GetDescription();
}


