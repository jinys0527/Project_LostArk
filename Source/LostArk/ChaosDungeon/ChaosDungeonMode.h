// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Monster/MonsterType.h"
#include "ChaosDungeonGameState.h"
#include "ChaosDungeonState.h"
#include "ChaosDungeonMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDungeonStateChanged, EDungeonState, NewState);

class AMonsterSpawner;
class ALostArkPlayerController;
class APlayerHUD;
class AMonster;
class ABossMonster;
class ABossMonsterSpawner;
class AChaosDungeonPortal;

/**
 * 
 */
UCLASS()
class LOSTARK_API AChaosDungeonMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AChaosDungeonMode();

	UPROPERTY(BlueprintAssignable, Category = "Dungeon")
	FOnDungeonStateChanged OnDungeonStateChanged;
	
	UFUNCTION()
	void OnProgressChanged(float NewProgress);

	UFUNCTION()
	void OnBossDead();

	AChaosDungeonPortal* BossPortal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> CompleteClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMonster> MonsterClass;

	APlayerHUD* PlayerHUD;

	ALostArkPlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RevivalCount = 0;

	TArray<AMonsterSpawner*> Spawners;

	void FindAllSpawners();

	void SpawnMonsterAtRandom(EMonsterType MonsterType);

	AChaosDungeonGameState* CurrentDungeonState;

	EDungeonState CurrentState;
	
	FTimerHandle CommonSpawnTimer;
	
	FTimerHandle NamedSpawnTimer;

	FVector Location;
	
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> PortalClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABossMonster> BossClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABossMonsterSpawner> BossMonsterSpawnerClass;

	void SetCurrentState(EDungeonState NewState);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	int Time;

	void StartTimer();

	void UpdateTime();

	FTimerHandle StageTimer;

	UFUNCTION(BlueprintCallable)
	void DeathPenalty();

	UFUNCTION()
	void HandleGameState(EDungeonState NewState);

	void Loading();

	void StartGame();

	void StartStage1();

	void StartStage2();

	void StartStage3();

	void EndGame();

	void Fail();
};
