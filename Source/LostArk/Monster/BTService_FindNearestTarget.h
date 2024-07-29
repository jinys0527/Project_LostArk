// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindNearestTarget.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UBTService_FindNearestTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_FindNearestTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void FindNearestTarget(UBehaviorTreeComponent& OwnerComp);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetToFollow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector DisttoTarget;
};
