// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsAttack : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	uint8 bIsEquipped : 1;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateAnimationProperties();

	virtual void NativeInitializeAnimation();

	class AMyPlayer* Player;
};
