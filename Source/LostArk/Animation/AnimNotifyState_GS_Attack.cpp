// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_GS_Attack.h"
#include "../Player/MyPlayer.h"

void UAnimNotifyState_GS_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if(Player)
	{ 
		Player->bIsAttack = true;
		Player->UpdateAnimationInstance();
	}
}

void UAnimNotifyState_GS_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		Player->bIsAttack = false;
		Player->UpdateAnimationInstance();
	}
}
