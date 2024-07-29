// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoAroundTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Player/MyPlayer.h"
#include "NavigationSystem.h"

UBTTask_GoAroundTarget::UBTTask_GoAroundTarget()
{
	NodeName = "Find New Location Around Target";
	RadiusRange = 300.0f;
}

EBTNodeResult::Type UBTTask_GoAroundTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMyPlayer* Target = Cast<AMyPlayer>(BlackboardComp->GetValueAsObject("TargettoFollow"));
	if (Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector OriginLocation = Target->GetActorLocation();
	FVector RandomLocation = GetRandomPointInRadius(OriginLocation, RadiusRange);

	BlackboardComp->SetValueAsVector("MoveToLocation", RandomLocation);

	return EBTNodeResult::Succeeded;
}

FVector UBTTask_GoAroundTarget::GetRandomPointInRadius(const FVector& Origin, float Radius)
{
	FNavLocation NavLocation;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSystem && NavSystem->GetRandomReachablePointInRadius(Origin, Radius, NavLocation))
	{
		return NavLocation.Location;
	}

	return Origin;
}
