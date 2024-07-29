// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsAlive.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster/Monster.h"

UBTDecorator_IsAlive::UBTDecorator_IsAlive()
{
	NodeName = "I am Alive";
}

bool UBTDecorator_IsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AMonster* Monster = Cast<AMonster>(OwnerComp.GetBlackboardComponent()->GetOwner());

	bool IsAlive = Monster->isAlive;

	return IsAlive;
}
