// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CalcDistToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/MyPlayer.h"
#include "../Monster/Monster.h"

UBTService_CalcDistToTarget::UBTService_CalcDistToTarget()
{
	NodeName = "Calculate Distance To Target";
}

void UBTService_CalcDistToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());
	AMyPlayer* Player = Cast<AMyPlayer>(BlackboardComp->GetValueAsObject("TargettoFollow"));

	if(AIController == nullptr)
	{
		return;
	}

	if(BlackboardComp == nullptr)
	{
		return;
	}

	if(Monster == nullptr)
	{
		return;
	}

	if (Player == nullptr)
	{
		return;
	}

	FVector PlayerLocation = Player->GetActorLocation();
	FVector MonsterLocation = Monster->GetActorLocation();

	float DistToTarget = FVector::Dist(MonsterLocation, PlayerLocation);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(DisttoTarget.SelectedKeyName, DistToTarget);
}
