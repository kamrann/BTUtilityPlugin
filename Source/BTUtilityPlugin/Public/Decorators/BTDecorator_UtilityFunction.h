// Copyright 2015 Cameron Angus. All Rights Reserved.
#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_UtilityFunction.generated.h"


/** 
 * Utility functions are responsible for providing a utility value for their associated node whenever the 
 * parent utility selector requests it.
 */
UCLASS(Abstract, HideCategories = (Condition))
class BTUTILITYPLUGIN_API UBTDecorator_UtilityFunction : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_UtilityFunction(const FObjectInitializer& ObjectInitializer);

	/** wrapper for node instancing: CalculateUtilityValue */
	float WrappedCalculateUtility(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

protected:
	/** Calculates the utility value of the associated behavior node. */
	virtual float CalculateUtilityValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};


//////////////////////////////////////////////////////////////////////////
// Inlines

