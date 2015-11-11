// Copyright 2015 Cameron Angus. All Rights Reserved.
#pragma once

#include "BTUtilitySelectionMethod.h"
#include "BTUtilitySelectionMethod_BlueprintBase.generated.h"

/*
@TODO: Look into what the purpose is of PropertyData in the other blueprint base classes, may need to
duplicate it.
*/


UCLASS(Abstract, Blueprintable)
class BTUTILITYPLUGIN_API UBTUtilitySelectionMethod_BlueprintBase : public UBTUtilitySelectionMethod
{
	GENERATED_UCLASS_BODY()

	/* UBTUtilitySelectionMethod interface */
	virtual void GenerateOrdering(TArray< float > const& UtilityValues, FUtilityExecutionOrdering& ExecutionOrdering) override;
	/**/

public:
	virtual FString GetDesc() override;
};



