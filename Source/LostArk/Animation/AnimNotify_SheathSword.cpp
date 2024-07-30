// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SheathSword.h"
#include "../Player/MyPlayer.h"

void UAnimNotify_SheathSword::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		Player->SetPlayerState(ECharacterState::Idle);
	}
}
