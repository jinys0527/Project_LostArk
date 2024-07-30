// Fill out your copyright notice in the Description page of Project Settings.


#include "../Animation/AnimInstance_Monster.h"
#include "../Monster/Monster.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimInstance_Monster::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
	{
		Speed = Monster->GetCharacterMovement()->Velocity.Size2D();
		bIsAlive = Monster->isAlive;
	}
}
