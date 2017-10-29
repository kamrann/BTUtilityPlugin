// Copyright 2015 Cameron Angus. All Rights Reserved.

#pragma once

#include "BTDecorator_UtilityFunction.h"
#include "BTDecorator_UtilityBlueprintBase.h"
#include "Union.h"


/** 
 * In order to avoid having to duplicate the code in UBTDecorator_BlueprintBase, we instead have two disparate base classes for utility functions -
 * one for C++ implementations, one for Blueprint.
 * 
 * This struct just gives us a simple interface for accessing the calculation from either kind.
 */
class FBTUtilityFunctionAccessor
{
protected:
	typedef const UBTDecorator_UtilityFunction* FNativeUtilFunc;
	typedef const UBTDecorator_UtilityBlueprintBase* FBlueprintUtilFunc;
	struct FNoUtilFunc {};

public:
	FBTUtilityFunctionAccessor(): UtilFunc(FNoUtilFunc{})
	{}

	FBTUtilityFunctionAccessor(FNativeUtilFunc NativeUtilFunc): UtilFunc(NativeUtilFunc)
	{}

	FBTUtilityFunctionAccessor(FBlueprintUtilFunc BPUtilFunc): UtilFunc(BPUtilFunc)
	{}

	inline TOptional< float > EvaluateUtility(FBehaviorTreeSearchData& SearchData)
	{
		if (UtilFunc.HasSubtype< FNativeUtilFunc >())
		{
			auto const Node = UtilFunc.GetSubtype< FNativeUtilFunc >();
			return Node->WrappedCalculateUtility(SearchData.OwnerComp, Node->GetNodeMemory<uint8 >(SearchData));
		}
		else if (UtilFunc.HasSubtype< FBlueprintUtilFunc >())
		{
			// Always instanced
			return UtilFunc.GetSubtype< FBlueprintUtilFunc >()->WrappedCalculateUtility();
		}
		else
		{
			return TOptional< float >();
		}
	}

protected:
	TUnion< FNoUtilFunc, FNativeUtilFunc, FBlueprintUtilFunc > UtilFunc;
};


