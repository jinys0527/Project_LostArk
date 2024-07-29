// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonGameState.h"

int32 AChaosDungeonGameState::CommonKillCount = 0;
int32 AChaosDungeonGameState::NamedKillCount = 0;
int32 AChaosDungeonGameState::BossKillCount = 0;

AChaosDungeonGameState::AChaosDungeonGameState()
{
	CurrentState = EChaosDungeonGameState::PreStart;
}

void AChaosDungeonGameState::IncreaseKillCount(EMonsterType MonsterType)
{
	switch (MonsterType)
	{
	case EMonsterType::Common:
		++CommonKillCount;
		break;
	case EMonsterType::Named:
		++NamedKillCount;
		break;
	case EMonsterType::Boss:
		++BossKillCount;
		break;
	}
}

void AChaosDungeonGameState::SetCurrentState(EChaosDungeonGameState NewState)
{
	CurrentState = NewState;
}
