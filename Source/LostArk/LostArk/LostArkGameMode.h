// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LostArkGameMode.generated.h"

class AChaosDungeonGameState;
class ULoadingTrixionWidget;
class AMyPlayer;

UCLASS(minimalapi)
class ALostArkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALostArkGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void StartLoadingCheck();

	void CheckLoadingComplete();

public:
	AMyPlayer* Player;

	FTimerHandle LoadingTimer;

	ULoadingTrixionWidget* LoadingTrixionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ULoadingTrixionWidget> LoadingTrixionWidgetClass;
};