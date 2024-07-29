// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RandomMoveSpeed.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Monster/Monster.h"

UBTService_RandomMoveSpeed::UBTService_RandomMoveSpeed()
{
	NodeName = "Set Random Move Speed";
}

void UBTService_RandomMoveSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return;
	}

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());
	if (Monster == nullptr)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Monster->GetCharacterMovement();
	if (MovementComponent == nullptr)
	{
		return;
	}

	float RandomSpeed = FMath::FRandRange(MinSpeed, MaxSpeed);
	MovementComponent->MaxWalkSpeed = RandomSpeed;
}

void UBTService_RandomMoveSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	TickNode(OwnerComp, NodeMemory, 0.0f);
}
