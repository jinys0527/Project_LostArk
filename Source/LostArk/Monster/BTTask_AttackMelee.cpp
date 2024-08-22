// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackMelee.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster/Monster.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystemComponent.h"
#include "../AbilitySystem/GameplayAbility/GA_Attack.h"

UBTTask_AttackMelee::UBTTask_AttackMelee()
{
	NodeName = "Attack";
	bNotifyTick = true;

	AttackRange = 50.0f;
}

EBTNodeResult::Type UBTTask_AttackMelee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AMyPlayer* TargetActor = Cast<AMyPlayer>(BlackboardComp->GetValueAsObject("TargettoFollow"));
	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());
	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Monster->Target = TargetActor;

	if (Monster->MonsterType == EMonsterType::Common)
	{
		AttackRange = 95.0f;
	}
	else if (Monster->MonsterType == EMonsterType::Named)
	{
		AttackRange = 100.0f;
	}
	else if (Monster->MonsterType == EMonsterType::Boss)
	{
		AttackRange = 115.0f;
	}

	float DistanceToTarget = FVector::Dist(Monster->GetActorLocation(), TargetActor->GetActorLocation());
	if (DistanceToTarget <= AttackRange)
	{
		PlayAttackAnimation(Monster, TargetActor);
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_AttackMelee::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_AttackMelee::PlayAttackAnimation(AMonster* Monster, AMyPlayer* Target)
{
	if (Target->isAlive)
	{
		if (Monster->DisttoTarget <= AttackRange)
		{
			UAbilitySystemComponent* AbilitySystemComponent = Monster->GetAbilitySystemComponent();
			if (AbilitySystemComponent)
			{
				AbilitySystemComponent->TryActivateAbilityByClass(UGA_Attack::StaticClass());
			}
		}
	}
}
