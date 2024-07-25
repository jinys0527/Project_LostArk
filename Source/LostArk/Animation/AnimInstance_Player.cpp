// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Player.h"
#include "../Player/MyPlayer.h"

void UAnimInstance_Player::UpdateAnimationProperties()
{
	if (Player)
	{
		bIsEquipped = Player->bIsEquipped;
		bIsAttack = Player->bIsAttack;
	}
}

void UAnimInstance_Player::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<AMyPlayer>(TryGetPawnOwner());
}
