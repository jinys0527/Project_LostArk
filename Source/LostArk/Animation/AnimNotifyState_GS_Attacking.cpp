// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyState_GS_Attacking.h"
#include "../Player/MyPlayer.h"
#include "../LostArk/LostArkPlayerController.h"
#include "../Weapon/GreatSword.h"
#include "../Monster/Monster.h"


void UAnimNotifyState_GS_Attacking::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		Player->SetPlayerState(ECharacterState::Attacking);
	}
}

void UAnimNotifyState_GS_Attacking::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());

	if (Player)
	{
		if (Player->Target.Num() != 0)
		{
			for (AMonster* Monster : Player->Target)
			{
				if (Monster)
				{
					Monster->bIsHitted = false;
				}
			}
		}
		Player->EquippedGreatSword->bIsOverlapped = false;

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
