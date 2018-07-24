// Copyright 2015 Cameron Angus. All Rights Reserved.
#pragma once

#include "Decorators/BTDecorator_UtilityFunction.h"
#include "BTDecorator_UtilityBlueprintBase.generated.h"

/*
@TODO: Look into what the purpose is of PropertyData in the other blueprint base classes, may need to
duplicate it.
*/


UCLASS(Abstract, Blueprintable)
class BTUTILITYPLUGIN_API UBTDecorator_UtilityBlueprintBase : public UBTDecorator_UtilityFunction
{
	GENERATED_UCLASS_BODY()

	/* UBTDecorator_UtilityFunction interface */
	virtual float CalculateUtilityValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	/**/

	virtual FString GetStaticDescription() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray< FString >& Values) const override;

	virtual void SetOwner(AActor* ActorOwner) override;

#if WITH_EDITOR
	virtual bool UsesBlueprint() const override;
#endif

protected:
	/** Cached AIController owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	AAIController* AIOwner;

	/** Cached actor owner of BehaviorTreeComponent. */
	UPROPERTY(Transient)
	AActor* ActorOwner;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Utility)
	float CalculateUtility(AAIController* OwnerController, APawn* ControlledPawn) const;
};


