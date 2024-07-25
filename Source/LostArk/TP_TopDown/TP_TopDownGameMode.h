// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChaosDungeonState.h"
#include "TP_TopDownGameMode.generated.h"

UCLASS(minimalapi)
class ATP_TopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_TopDownGameMode();

	EChaosDungeonGameState CurrentState;

	void SetCurrentState(EChaosDungeonGameState NewState);
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void HandleGameState(EChaosDungeonGameState NewState);

	void Loading();

	void StartGame();

	void StartStage1();

	void StartStage2();

	void StartStage3();

	void EndGame();
};



