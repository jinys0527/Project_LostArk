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
class ULoadingLogHillWidget;

/**
 *
 */
UCLASS()
class LOSTARK_API AChaosDungeonMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AChaosDungeonMode();
	UFUNCTION()
	void OnProgressChanged(float NewProgress);

	UFUNCTION()
	void OnBossDead();

	void FindAllSpawners();

	void SpawnMonsterAtRandom(EMonsterType MonsterType);

	void SetCurrentState(EDungeonState NewState);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void StartTimer();

	void UpdateTime();

	UFUNCTION(BlueprintCallable)
	void DeathPenalty();

	UFUNCTION()
	void HandleGameState(EDungeonState NewState);

	void StartGame();

	void StartStage1();

	void StartStage2();

	void StartStage3();

	void EndGame();

	void Fail();

	void StartLoadingCheck();

	void CheckLoadingComplete();

public:

	FTimerHandle LoadingTimer;

	ULoadingLogHillWidget* LoadingLogHillWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ULoadingLogHillWidget>> LoadingLogHillWidgetClass;

	UPROPERTY(BlueprintAssignable, Category = "Dungeon")
	FOnDungeonStateChanged OnDungeonStateChanged;

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

	UPROPERTY(BlueprintReadOnly)
	int Time;

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

	FTimerHandle StageTimer;
};
