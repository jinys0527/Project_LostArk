// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API ABossMonster : public AMonster
{
	GENERATED_BODY()
public:
	ABossMonster();

	TSubclassOf<ABossMonster> BossClass;

	static int32 BossWidgetCount;

	virtual void BeginPlay() override;
};
