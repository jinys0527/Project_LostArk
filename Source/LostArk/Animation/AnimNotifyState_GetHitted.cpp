// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_GetHitted.h"
#include "../Player/MyPlayer.h"

void UAnimNotifyState_GetHitted::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());
	if (Player)
	{
		Player->PrevState = Player->CurrentState;
		Player->SetPlayerState(ECharacterState::GetHitting);
	}
}

void UAnimNotifyState_GetHitted::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());
	if (Player)
	{
		Player->SetPlayerState(Player->PrevState);
	}
}
