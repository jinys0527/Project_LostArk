// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_MyConeCheck.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UBTDecorator_MyConeCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_MyConeCheck();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector TargetToFollow;
};
