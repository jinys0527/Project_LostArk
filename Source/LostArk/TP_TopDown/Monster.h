// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonster();

	FStat Stat;

	virtual void PlayDead();

	virtual void PlayHitReaction();

	virtual void Move();

	virtual void Attack();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
