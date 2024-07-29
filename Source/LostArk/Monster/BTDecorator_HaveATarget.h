// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_HaveATarget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UBTDecorator_HaveATarget : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTDecorator_HaveATarget();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
