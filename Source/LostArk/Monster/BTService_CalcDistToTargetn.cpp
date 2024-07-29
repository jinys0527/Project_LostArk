// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CalcDistToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/MyPlayer.h"

UBTService_CalcDistToTarget::UBTService_CalcDistToTarget()
{
	NodeName = "Calculate Distance To Target";
}

void UBTService_CalcDistToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AMyPlayer* Player = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargettoFollow"));

	if (Player == nullptr)
	{
		return;
	}

	FVector PlayerLocation = Player->GetActorLocation();
	FVector MonsterLocation = OwnerComp.GetBlackboardComponent()->GetOwner()->GetActorLocation();

	float DistToTarget = FVector::Dist(MonsterLocation, PlayerLocation);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(DisttoTarget.SelectedKeyName, DistToTarget);
}
