// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonCore.h"
#include "MonsterSpawner.h"
#include "../Monster/NamedMonster.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/PlayerHUD.h"
#include "../LostArk/LostArkPlayerController.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/ProgressWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "ChaosDungeonGameState.h"

// Sets default values
AChaosDungeonCore::AChaosDungeonCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChaosDungeonCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChaosDungeonCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChaosDungeonCore::SpawnSpawner()
{
	FVector Location = GetActorLocation();
	Location.Z = 102.0f;
	FRotator Rotation = GetActorRotation();
	Spawner = GetWorld()->SpawnActor<AMonsterSpawner>(MonsterSpawnerClass, Location, Rotation);

	for (int i = 0; i < 3; ++i)
	{
		Spawner->SpawnMonster(EMonsterType::Common, Spawner->GetActorLocation());
	}

	UWorld* World = GetWorld();

	ALostArkPlayerController* PC = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	if (World)
	{
		AGameStateBase* CurrentState = World->GetGameState();
		if (CurrentState)
		{
			AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(CurrentState);
			ANamedMonster* Named = GetWorld()->SpawnActor<ANamedMonster>(NamedMonsterClass, Location, Rotation);
			if (Named)
			{
				PlayerHUD->OverlayWidget->WBPProgress->BindToMonster(Named);
				PlayerHUD->OverlayWidget->WBPMiniMapLogHill->AddMonster(Named);
				++ChaosDungeonState->CurrentMonsterCount;
				++ChaosDungeonState->StageNamedCount;
			}
		}
	}
	Spawner->Destroy();
}

