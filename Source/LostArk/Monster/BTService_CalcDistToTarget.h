// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CalcDistToTarget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UBTService_CalcDistToTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_CalcDistToTarget();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetToFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector DisttoTarget;
};
