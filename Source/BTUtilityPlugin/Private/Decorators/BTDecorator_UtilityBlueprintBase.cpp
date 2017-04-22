// Copyright 2015 Cameron Angus. All Rights Reserved.

#include "Decorators/BTDecorator_UtilityBlueprintBase.h"

#include "AIController.h"


UBTDecorator_UtilityBlueprintBase::UBTDecorator_UtilityBlueprintBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = TEXT("UnknownUtilFunc");

	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;

/*	@TODO: Look into how this is done in BTDecorator_BlueprintBase.

	UClass* StopAtClass = UBTDecorator_UtilityBlueprintBase::StaticClass();
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		BlueprintNodeHelpers::CollectPropertyData(this, StopAtClass, PropertyData);
	}
	*/
}

float UBTDecorator_UtilityBlueprintBase::CalculateUtilityValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return CalculateUtility(AIOwner, Cast< APawn >(ActorOwner));
}

FString UBTDecorator_UtilityBlueprintBase::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}

void UBTDecorator_UtilityBlueprintBase::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray< FString >& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}

void UBTDecorator_UtilityBlueprintBase::SetOwner(AActor* InActorOwner)
{
	ActorOwner = InActorOwner;
	AIOwner = Cast< AAIController >(InActorOwner);
}


#if WITH_EDITOR

bool UBTDecorator_UtilityBlueprintBase::UsesBlueprint() const
{
	return true;
}

#endif // WITH_EDITOR


