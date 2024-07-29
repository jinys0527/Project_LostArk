// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonGameState.h"

AChaosDungeonGameState::AChaosDungeonGameState()
{
	CurrentState = EDungeonState::PreStart;
	MonsterMaxSpawnLimit = 6;
	NamedMonsterMaxSpawnLimit = 2;
	CurrentMonsterCount = 0;
	StageNamedCount = 0;
	StageCommonCount = 0;
}

void AChaosDungeonGameState::SetCurrentState(EDungeonState NewState)
{
	CurrentState = NewState;
}
