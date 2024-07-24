// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_GS_Attacking.h"
#include "../Player/MyPlayer.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"


void UAnimNotifyState_GS_Attacking::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		Player->bIsAttacking = true;
		Player->SetPlayerState(ECharacterState::Attacking);
	}
}

void UAnimNotifyState_GS_Attacking::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		Player->bIsAttacking = false;
		Player->SetPlayerState(ECharacterState::Battle);
	}
}