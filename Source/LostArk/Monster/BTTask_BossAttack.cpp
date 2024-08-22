// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster/Monster.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystemComponent.h"
#include "../AbilitySystem/GameplayAbility/GA_BossFire.h"

UBTTask_BossAttack::UBTTask_BossAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	float DistanceToTarget = FVector::Dist(Monster->GetActorLocation(), TargetActor->GetActorLocation());
	if (DistanceToTarget <= SkillRange)
	{
		UAbilitySystemComponent* SourceASC = Monster->GetAbilitySystemComponent();
		if (SourceASC)
		{
			SourceASC->TryActivateAbilityByClass(UGA_BossFire::StaticClass());
		}
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}