// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Monster/MonsterType.h"
#include "ChaosDungeonGameState.h"
#include "ChaosDungeonState.h"
#include "ChaosDungeonMode.generated.h"

class AMonsterSpawner;
class ATP_TopDownPlayerController;
class APlayerHUD;
/**
 * 
 */
UCLASS()
class LOSTARK_API AChaosDungeonMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AChaosDungeonMode();

	APlayerHUD* PlayerHUD;

	ATP_TopDownPlayerController* PC;

	TArray<AMonsterSpawner*> Spawners;

	void FindAllSpawners();

	void SpawnMonsterAtRandom(EMonsterType MonsterType);

	AChaosDungeonGameState* CurrentDungeonState;

	EDungeonState CurrentState;
	
	FTimerHandle CommonSpawnTimer;
	
	FTimerHandle NamedSpawnTimer;

	FTimerHandle BossTimer;

	FTimerHandle CheckTimer;

	bool CheckSpawnPortal(float Percent);

	bool CheckSpawnBoss(float Percent);

	void SetCurrentState(EDungeonState NewState);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void HandleGameState(EDungeonState NewState);

	void Loading();

	void StartGame();

	void StartStage1();

	void StartStage2();

	void StartStage3();

	void EndGame();

	void Fail();
};
