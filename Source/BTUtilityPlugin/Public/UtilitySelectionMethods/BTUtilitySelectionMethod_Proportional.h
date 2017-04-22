// Copyright 2015 Cameron Angus. All Rights Reserved. 

#pragma once

#include "BTUtilityTypes.h"


namespace UtilitySelection
{
	/**
	* Proportional selection.
	* Nodes are chosen with a probability proportional to their utility value.
	*/
	void ProportionalOrdering(TArray< float > const& UtilityValues, FUtilityExecutionOrdering& ExecutionOrdering);
}



