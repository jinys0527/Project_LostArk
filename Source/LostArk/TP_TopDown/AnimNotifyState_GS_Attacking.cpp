// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_GS_Attacking.h"
#include "MyPlayer.h"
#include "TP_TopDownPlayerController.h"


void UAnimNotifyState_GS_Attacking::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		if (ATP_TopDownPlayerController* PC = Cast< ATP_TopDownPlayerController>(Player->GetController()))
		{
			Player->DisableInput(PC);
		}

		Player->bIsAttacking = true;
	}
}

void UAnimNotifyState_GS_Attacking::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		Player->bIsAttacking = false;
		if (ATP_TopDownPlayerController* PC = Cast< ATP_TopDownPlayerController>(Player->GetController()))
		{
			//Player->EnableInput(PC);
		}
	}
}
