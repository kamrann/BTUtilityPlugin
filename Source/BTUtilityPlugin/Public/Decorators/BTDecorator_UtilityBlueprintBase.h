// Copyright 2015 Cameron Angus. All Rights Reserved.
#pragma once

#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BTDecorator_UtilityBlueprintBase.generated.h"


UCLASS(Abstract, Blueprintable)
class BTUTILITYPLUGIN_API UBTDecorator_UtilityBlueprintBase : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTDecorator_UtilityBlueprintBase();

public:
	float WrappedCalculateUtility() const;

protected:
	/** The utility calculation function, to be implemented in derived blueprints. */
	UFUNCTION(BlueprintImplementableEvent, Category = Utility)
	float CalculateUtility(AAIController* OwnerController, APawn* ControlledPawn) const;
};


