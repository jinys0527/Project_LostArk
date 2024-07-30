// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/BaseCharacter.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Player.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API UAnimInstance_Player : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	uint8 bIsAlive : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Timer")
	int32 TimeCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsAttack : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsEquipped : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerState")
	ECharacterState CurrentState;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	class AMyPlayer* Player;
};
