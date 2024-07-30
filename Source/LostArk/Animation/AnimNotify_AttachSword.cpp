// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttachSword.h"
#include "../Player/MyPlayer.h"
#include "../Weapon/GreatSword.h"

void UAnimNotify_AttachSword::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMyPlayer* Player = Cast<AMyPlayer>(MeshComp->GetOwner());
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	if (Player)
	{
		Player->EquippedGreatSword->AttachToComponent(Player->GetMesh(), AttachmentRules, TEXT("Weapon_Right"));
		Player->SetPlayerState(ECharacterState::Battle);
	}
}
