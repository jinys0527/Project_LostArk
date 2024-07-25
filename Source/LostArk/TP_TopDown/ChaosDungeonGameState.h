// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ChaosDungeonState.h"
#include "../Monster/MonsterType.h"
#include "ChaosDungeonGameState.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARK_API AChaosDungeonGameState : public AGameState
{
	GENERATED_BODY()
public:
	AChaosDungeonGameState();

	static int32 CommonKillCount;

	static int32 NamedKillCount;

	static int32 BossKillCount;

	void IncreaseKillCount(EMonsterType MonsterType);

	EChaosDungeonGameState CurrentState;

	void SetCurrentState(EChaosDungeonGameState NewState);
};
