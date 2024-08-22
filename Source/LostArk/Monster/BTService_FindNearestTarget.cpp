// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindNearestTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/MyPlayer.h"

UBTService_FindNearestTarget::UBTService_FindNearestTarget()
{
	NodeName = "Find Nearest Target";
}

void UBTService_FindNearestTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FindNearestTarget(OwnerComp);
}

void UBTService_FindNearestTarget::FindNearestTarget(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (AIController && BlackboardComp)
	{
		TArray<AActor*> TaggedActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Player", TaggedActors);

		AActor* NearestTarget = nullptr;
		float NearestDistance = FLT_MAX;

		APawn* AIPawn = AIController->GetPawn();
		FVector AILocation = AIPawn->GetActorLocation();

		for (AActor* Actor : TaggedActors)
		{
			AMyPlayer* Player = Cast<AMyPlayer>(Actor);
			if (Player && Player->isAlive)
			{
				float DistanceSq = FVector::Dist(AILocation, Actor->GetActorLocation());
				if (DistanceSq < NearestDistance)
				{
					NearestDistance = DistanceSq;
					NearestTarget = Actor;
				}
			}
		}

		if (NearestTarget)
		{
			BlackboardComp->SetValueAsObject(TargetToFollow.SelectedKeyName, NearestTarget);
			BlackboardComp->SetValueAsFloat(DisttoTarget.SelectedKeyName, NearestDistance);
		}
		else
		{
			BlackboardComp->ClearValue(TargetToFollow.SelectedKeyName);
			BlackboardComp->ClearValue(DisttoTarget.SelectedKeyName);
		}
	}
}
