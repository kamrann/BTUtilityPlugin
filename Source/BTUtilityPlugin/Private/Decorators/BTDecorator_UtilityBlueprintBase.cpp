// Copyright 2015 Cameron Angus. All Rights Reserved.

#include "Decorators/BTDecorator_UtilityBlueprintBase.h"

#include "AIController.h"


UBTDecorator_UtilityBlueprintBase::UBTDecorator_UtilityBlueprintBase()
{
	NodeName = TEXT("UnknownUtilFunc");
}

float UBTDecorator_UtilityBlueprintBase::WrappedCalculateUtility() const
{
	return CalculateUtility(AIOwner, Cast< APawn >(ActorOwner));
}

