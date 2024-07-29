// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsAlive.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster/Monster.h"
#include "AIController.h"

UBTDecorator_IsAlive::UBTDecorator_IsAlive()
{
	NodeName = "I am Alive";
}

bool UBTDecorator_IsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	bool IsAlive = Monster->isAlive;

	return IsAlive;
}
