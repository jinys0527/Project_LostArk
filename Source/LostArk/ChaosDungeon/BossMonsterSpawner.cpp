// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonsterSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "../Monster/BossMonster.h"
#include "../LostArk/LostArkPlayerController.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "../ChaosDungeon/ChaosDungeonGameState.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossMonsterSpawner::ABossMonsterSpawner()
{
	Center = GetActorLocation();
}

ABossMonster* ABossMonsterSpawner::SpawnBossMonster(FVector SpawnLocation, FRotator SpawnRotation)
{
	ALostArkPlayerController* PC = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	ABossMonster* Boss = nullptr;
	MonsterSizeRadius = 62.0f;

	AGameStateBase* CurrentState = GetWorld()->GetGameState();
	if (CurrentState)
	{
		AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(CurrentState);
		Boss = GetWorld()->SpawnActor<ABossMonster>(BossClass, SpawnLocation, SpawnRotation);

		PlayerHUD->OverlayWidget->WBPMiniMapLogHill->AddMonster(Boss);
		++ChaosDungeonState->CurrentMonsterCount;
	}

	return Boss;
}