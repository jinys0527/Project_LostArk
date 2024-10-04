// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArkGameMode.h"
#include "LostArkPlayerController.h"
#include "../Player/MyPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "../ChaosDungeon/ChaosDungeonGameInstance.h"
#include "Kismet/GameplayStatics.h"

ALostArkGameMode::ALostArkGameMode()
{
	
}

void ALostArkGameMode::BeginPlay()
{
	UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

		Player->MaintainStatus(GameInstance);
	}
}

void ALostArkGameMode::Tick(float DeltaSeconds)
{
	
}