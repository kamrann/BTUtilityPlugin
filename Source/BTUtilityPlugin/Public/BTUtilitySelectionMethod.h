// Copyright 2015 Cameron Angus. All Rights Reserved.
#pragma once

#include "BTUtilityTypes.h"
#include "UObject/Object.h"
#include "BTUtilitySelectionMethod.generated.h"


/** 
 * A utility selection method chooses from a list of options each of which has an associated utility value.
 */
UCLASS(Abstract, EditInlineNew)
class BTUTILITYPLUGIN_API UBTUtilitySelectionMethod : public UObject
{
	GENERATED_BODY()

public:
	static const int32 NoSelection = -1;

public:
	virtual int32 SelectOption(TArray< float > const& UtilityValues);
	virtual void GenerateOrdering(TArray< float > const& UtilityValues, FUtilityExecutionOrdering& ExecutionOrdering);
};


