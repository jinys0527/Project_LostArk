// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP_TopDownGameMode.generated.h"

class AChaosDungeonGameState;

UCLASS(minimalapi)
class ATP_TopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATP_TopDownGameMode();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};