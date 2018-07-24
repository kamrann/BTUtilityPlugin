// Copyright 2015 Cameron Angus. All Rights Reserved. /
#pragma once

#include "Decorators/BTDecorator_UtilityFunction.h"
#include "BTDecorator_UtilityConstant.generated.h"

/**
* Constant utility function.
* The associated node's utility value is specified as a constant value.
*/
UCLASS(Meta = (DisplayName = "Constant Utility", Category = "Utility Functions"))
class BTUTILITYPLUGIN_API UBTDecorator_UtilityConstant : public UBTDecorator_UtilityFunction
{
	GENERATED_BODY()

public:
	UBTDecorator_UtilityConstant(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Utility")
	float UtilityValue;

	virtual FString GetStaticDescription() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

protected:
	virtual float CalculateUtilityValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};


