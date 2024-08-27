// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Attack.h"
#include "../Player/MyPlayer.h"

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		if (Player->Target.Num() == 0 && Player->PrevState != ECharacterState::Combat)
		{
			Player->SetPlayerState(ECharacterState::Battle);
		}
		else
		{
			Player->SetPlayerState(ECharacterState::Combat);
		}
	}
}
