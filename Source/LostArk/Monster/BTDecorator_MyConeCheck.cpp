// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_MyConeCheck.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Player/MyPlayer.h"
#include "../Monster/Monster.h"

UBTDecorator_MyConeCheck::UBTDecorator_MyConeCheck()
{
	NodeName = "Cone Check";
	
}

bool UBTDecorator_MyConeCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return false;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return false;
	}

	AMyPlayer* Target = Cast<AMyPlayer>(BlackboardComp->GetValueAsObject("TargettoFollow"));
	if (Target == nullptr)
	{
		return false;
	}

	AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

	FVector TargetLocation = Target->GetActorLocation();
	FVector MonsterLocation = Monster->GetActorLocation();
	FVector MonsterForward = Monster->GetActorForwardVector();

	FVector Normal = (TargetLocation - MonsterLocation).GetUnsafeNormal();
	float Product = FVector::DotProduct(Normal, MonsterForward);

	bool Valid = IsValid(Target->InputComponent);

	if(Valid)
	{
		return FMath::Acos(Product) <= Angle;
	}

	return false;
}
