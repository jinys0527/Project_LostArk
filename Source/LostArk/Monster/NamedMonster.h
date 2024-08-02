// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "NamedMonster.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API ANamedMonster : public AMonster
{
	GENERATED_BODY()
public:
	ANamedMonster();

	virtual void PlayDead() override;
};
