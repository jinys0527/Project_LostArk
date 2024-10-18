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
class LOSTARK_API AChaosDungeonGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AChaosDungeonGameState();

	int32 MonsterMaxSpawnLimit;

	int32 NamedMonsterMaxSpawnLimit;

	int32 CurrentMonsterCount;

	int32 StageCommonCount;

	int32 StageAliveCommonCount;

	int32 StageNamedCount;

	int32 StageAliveNamedCount;

	int32 StageCommonLimit;

	int32 StageNamedLimit;

	EDungeonState CurrentState;

	void SetCurrentState(EDungeonState NewState);
};
