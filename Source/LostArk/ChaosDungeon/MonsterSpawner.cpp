// Fill out your copyright notice in the Description page of Project Settings.


#include "../ChaosDungeon/MonsterSpawner.h"
#include "../ChaosDungeon/ChaosDungeonGameState.h"
#include "../Monster/Monster.h"
#include "../Monster/NamedMonster.h"
#include "../Monster/BossMonster.h"
#include "../Player/PlayerHUD.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Monster/MonsterAIController.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../AbilitySystem/LostArkMonsterAttributeSet.h"
#include "../Widget/OverlayWidgetController.h"
#include "../Widget/ProgressWidget.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
	Center = GetActorLocation();
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterSpawner::SpawnMonster(EMonsterType MonsterType)
{
	if (MonsterType == EMonsterType::Common)
	{
		MaxRadius = CommonMaxRadius;
	}
	else if (MonsterType == EMonsterType::Named)
	{
		MaxRadius = NamedMaxRadius;
	}
	int RadiusRange = FMath::RandRange(1, 2);
	int AngleRange = FMath::RandRange(1, 4);

	switch (RadiusRange)
	{
	case 1:
		Radius = FMath::FRandRange(MaxRadius / 3 + 1, MaxRadius * 2 / 3);
		break;

	case 2:
		Radius = FMath::FRandRange(2 * MaxRadius / 3 + 1, MaxRadius);
		break;
	}
	
	switch (AngleRange)
	{
	case 1:
		Angle = FMath::FRandRange(0.0f, 90.0f);
		break;
	case 2:
		Angle = FMath::FRandRange(91.0f, 180.0f);
		break;
	case 3:
		Angle = FMath::FRandRange(181.0f, 270.0f);
		break;
	case 4:
		Angle = FMath::FRandRange(271.0f, 360.0f);
		break;
	}

	float SpawnX = Center.X + (FMath::Cos(FMath::DegreesToRadians(Angle)) * Radius);
	float SpawnY = Center.Y + (FMath::Sin(FMath::DegreesToRadians(Angle)) * Radius);
	float SpawnZ = 102.f;

	FVector SpawnLocation(SpawnX, SpawnY, SpawnZ);

	FRotator SpawnRotation = FRotator::ZeroRotator;

	UWorld* World = GetWorld();

	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	if (World)
	{
		AGameStateBase* CurrentState = World->GetGameState();
		if (CurrentState)
		{
			AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(CurrentState);

			switch (MonsterType)
			{
			case EMonsterType::Common:
				MonsterSizeRadius = 48.0f;

				if ((ChaosDungeonState->CurrentMonsterCount < ChaosDungeonState->MonsterMaxSpawnLimit) && (ChaosDungeonState->StageCommonCount < ChaosDungeonState->StageCommonLimit))
				{
					AMonster* Monster = World->SpawnActor<AMonster>(MonsterClass, SpawnLocation, SpawnRotation);
					if (Monster)
					{
						PlayerHUD->OverlayWidget->WBPProgress->BindToMonster(Monster);
						PlayerHUD->OverlayWidget->WBPMiniMapLogHill->AddMonster(Monster);
						++ChaosDungeonState->CurrentMonsterCount;
						++ChaosDungeonState->StageCommonCount;
					}
				}

				break;
			case EMonsterType::Named:
				MonsterSizeRadius = 50.0f;
				if (((ChaosDungeonState->CurrentMonsterCount + ChaosDungeonState->StageNamedCount) < ChaosDungeonState->MonsterMaxSpawnLimit) && (ChaosDungeonState->StageNamedCount < ChaosDungeonState->StageNamedLimit))
				{
					ANamedMonster* NamedMonster = World->SpawnActor<ANamedMonster>(NamedMonsterClass, SpawnLocation, SpawnRotation);
					if(NamedMonster)
					{
						PlayerHUD->OverlayWidget->WBPProgress->BindToMonster(NamedMonster);
						PlayerHUD->OverlayWidget->WBPMiniMapLogHill->AddMonster(NamedMonster);
						++ChaosDungeonState->CurrentMonsterCount;
						++ChaosDungeonState->StageNamedCount;
					}
				}
				break;
			}
		}
	}
}