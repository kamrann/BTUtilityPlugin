// Copyright 2015 Cameron Angus. All Rights Reserved. /
#pragma once

#include "BTUtilitySelectionMethod.h"


namespace UtilitySelection
{
	/**
	* Chooses the node with the highest utility value.
	*/
	void PriorityOrdering(TArray< float > const& UtilityValues, FUtilityExecutionOrdering& ExecutionOrdering);
}


