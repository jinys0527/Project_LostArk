// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Player.h"
#include "../Player/MyPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Player = Cast<AMyPlayer>(TryGetPawnOwner());
	if (IsValid(Player))
	{
		Speed = Player->GetCharacterMovement()->Velocity.Size2D();
		CurrentState = Player->CurrentState;
	}
}
