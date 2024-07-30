// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_MonsterAttack.h"
#include "../Monster/Monster.h"

void UAnimNotifyState_MonsterAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());

	if (Monster)
	{
		Monster->bIsAttack = true;
	}
}

void UAnimNotifyState_MonsterAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AMonster* Monster = Cast<AMonster>(MeshComp->GetOwner());

	if (Monster)
	{
		Monster->bIsAttack = false;
	}
}
