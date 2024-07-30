// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackMelee.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Monster/Monster.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"

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

	if (Monster->MonsterType == EMonsterType::Common)
	{
		AttackRange = 88.0f;
	}
	else if (Monster->MonsterType == EMonsterType::Named)
	{
		AttackRange = 96.0f;
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
		Monster->Attack();

		FTimerHandle AttackTimer;

		if (Monster->MonsterType == EMonsterType::Common)
		{
			GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this, Monster, Target]() {
				if (Monster->bIsAttack)
				{
					UGameplayStatics::ApplyDamage(Target, (Monster->CalcDamage(Monster->Stat.ATK, 100.f - Target->Stat.Block)), Target->GetController(), Monster, UDamageType::StaticClass());
				}
				}, 0.85f, false);
		}
		else if (Monster->MonsterType == EMonsterType::Named)
		{
			GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this, Monster, Target]() {
				if (Monster->bIsAttack)
				{
					UGameplayStatics::ApplyDamage(Target, (Monster->CalcDamage(Monster->Stat.ATK, 100.f - Target->Stat.Block)), Target->GetController(), Monster, UDamageType::StaticClass());
				}
				}, 0.22f, false);
		}
	}
}
