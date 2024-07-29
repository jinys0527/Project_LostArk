// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonMode.h"
#include "Kismet/GameplayStatics.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "MonsterSpawner.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/TimerWidget.h"
#include "../Widget/ProgressWidget.h"
#include "Components/ProgressBar.h"
#include "ChaosDungeonPortal.h"

AChaosDungeonMode::AChaosDungeonMode()
{
	CurrentState = EDungeonState::PreStart;
}

void AChaosDungeonMode::FindAllSpawners()
{
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonsterSpawner::StaticClass(), FoundSpawners);

	for (AActor* Actor : FoundSpawners)
	{
		AMonsterSpawner* Spawner = Cast<AMonsterSpawner>(Actor);

		if (Spawner)
		{
			Spawners.Add(Spawner);
		}
	}
}

void AChaosDungeonMode::SpawnMonsterAtRandom(EMonsterType MonsterType)
{
	if (Spawners.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, Spawners.Num() - 1);

		AMonsterSpawner* SelectedSpawner = Spawners[RandomIndex];
		if (SelectedSpawner)
		{
			SelectedSpawner->SpawnMonster(MonsterType);

			switch (MonsterType)
			{
				case EMonsterType::Common:
					if (CurrentDungeonState->StageCommonCount == CurrentDungeonState->StageCommonLimit)
					{
						GetWorld()->GetTimerManager().ClearTimer(CommonSpawnTimer);
					}
					break;
				case EMonsterType::Named:
					if (CurrentDungeonState->StageNamedCount == CurrentDungeonState->StageNamedLimit)
					{
						GetWorld()->GetTimerManager().ClearTimer(NamedSpawnTimer);
					}
			}
			
		}
	}
}

bool AChaosDungeonMode::CheckSpawnPortal(float Percent)
{
	if (Percent >= 0.18f && Percent <= 0.2f)
	{
		//포탈 소환
		return true;
	}
	return false;
}

bool AChaosDungeonMode::CheckSpawnBoss(float Percent)
{
	if (Percent >= 0.45f && Percent <= 0.5f)
	{
		//가운데 보스 소환
		//잡으면 보스 나온 스포너에 포탈 소환
	}
	return false;
}

void AChaosDungeonMode::SetCurrentState(EDungeonState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;
	HandleGameState(NewState);

	CurrentDungeonState->SetCurrentState(NewState);
}

void AChaosDungeonMode::BeginPlay()
{
	CurrentDungeonState = GetWorld()->GetGameState<AChaosDungeonGameState>();
	PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	//생성자에서 하면 Crash

}

void AChaosDungeonMode::Tick(float DeltaSeconds)
{
}

void AChaosDungeonMode::HandleGameState(EDungeonState NewState)
{
	switch (NewState)
	{
	case EDungeonState::PreStart:
		Loading();
		break;
	case EDungeonState::Start:
		StartGame();
		break;
	case EDungeonState::Stage1:
		StartStage1();
		break;
	case EDungeonState::Stage2:
		StartStage2();
		break;
	case EDungeonState::Stage3:
		StartStage3();
		break;
	case EDungeonState::End:
		EndGame();
		break;
	}
}

void AChaosDungeonMode::Loading()
{
	//로딩 위젯?
	HandleGameState(CurrentState);
}

//환산 일반 25마리 2.5퍼 네임드 50마리 5퍼 보스 100마리 10퍼 
//목표 1000마리
//공격모션 1.2초 일반몹 마리당 3대		3.6초
//네임드 일반몹 1.5배 3.6*1.5초		5.4초
//보스 네임드 1.5배 3.6*1.5*1.5초		8.1초
//타이머 죽으면 15초 감소, 타임오버시 Fail로
void AChaosDungeonMode::StartGame()
{
	if (PlayerHUD->TimerClass)
	{
		PlayerHUD->Timer = CreateWidget<UTimerWidget>(PC, PlayerHUD->TimerClass);
		if (PlayerHUD->Timer)
		{
			PlayerHUD->Timer->AddToViewport();
		}
	}

	if (PlayerHUD->ProgressClass)
	{
		PlayerHUD->Progress = CreateWidget<UProgressWidget>(PC, PlayerHUD->ProgressClass);
		if (PlayerHUD->Progress)
		{
			PlayerHUD->Progress->AddToViewport();
		}
	}
	CurrentDungeonState->SetCurrentState(EDungeonState::Stage1);
	HandleGameState(CurrentState);
}

void AChaosDungeonMode::StartStage1()
{
	if (PlayerHUD)
	{
		if (PlayerHUD->Timer)
		{
			if (PlayerHUD->Timer->bIsEnd)
			{
				SetCurrentState(EDungeonState::Fail);
				HandleGameState(CurrentState);
			}

			PlayerHUD->Timer->InitTime();
			PlayerHUD->Timer->StartTimer();
		}
	}

	CurrentDungeonState->StageCommonLimit = 10;

	FindAllSpawners();

	GetWorld()->GetTimerManager().SetTimer(
		CommonSpawnTimer,
		[this]()
		{
			SpawnMonsterAtRandom(EMonsterType::Common);
		}, 
		1.5f, 
		true);

	GetWorld()->GetTimerManager().SetTimer(
		CheckTimer,
		[this]()
		{
			if (PlayerHUD && PlayerHUD->Progress && PlayerHUD->Progress->ChaosDungeonProgressBar)
			{
				float CurrentPercent = PlayerHUD->Progress->ChaosDungeonProgressBar->GetPercent();
				if (CheckSpawnPortal(CurrentPercent))
				{
					//GetWorld()->SpawnActor<AChaosDungeonPortal>(AChaosDungeonPortal::StaticClass(), );
				}
			}
		},
		1.5f,
		true);

	//랜덤 일반몹 소환 최대 마리수 짧은 텀 시간 제한
	//18~20% 포탈 소환(파란색)
	//일반 8마리 1분 12초
	//포탈 이동시 포탈 상호작용 시 Set(Stage2) -> Handle
}

void AChaosDungeonMode::StartStage2()
{
	if (PlayerHUD)
	{
		if (PlayerHUD->Timer)
		{
			if (PlayerHUD->Timer->bIsEnd)
			{
				SetCurrentState(EDungeonState::Fail);
				HandleGameState(CurrentState);
			}

			PlayerHUD->Timer->InitTime();
			PlayerHUD->Timer->StartTimer();
		}
	}

	CurrentDungeonState->StageCommonLimit = 4;
	CurrentDungeonState->StageNamedLimit = 4;

	FindAllSpawners();

	GetWorld()->GetTimerManager().SetTimer(
		CommonSpawnTimer,
		[this]()
		{
			SpawnMonsterAtRandom(EMonsterType::Common);
		},
		1.5f,
		true);

	GetWorld()->GetTimerManager().SetTimer(
		NamedSpawnTimer,
		[this]()
		{
			SpawnMonsterAtRandom(EMonsterType::Named);
		},
		3.0f,
		true);



	//랜덤 일반몹 + 네임드 소환(최대 2마리, 마리수)
	//45~50% 보스 소환(진행도)
	//보스 잡으면 포탈소환(검은색)
	//네임드 대충 4마리 20퍼 일반 10퍼 4마리, 일반은 대충 계속 소환
	//보스 10퍼 100마리 
	//1분 5.7초
	//포탈 이동시 Set(Stage3) -> Handle
}

void AChaosDungeonMode::StartStage3()
{
	if (PlayerHUD)
	{
		if (PlayerHUD->Timer)
		{
			if (PlayerHUD->Timer->bIsEnd)
			{
				SetCurrentState(EDungeonState::Fail);
				HandleGameState(CurrentState);
			}

			PlayerHUD->Timer->InitTime();
			PlayerHUD->Timer->StartTimer();
		}
	}
	//랜덤 일반몹 + 네임드 소환 - 빨간결정 깰 시 
	//스포너를 이동시키며 일반몹 좀 잡으면 결정 소환 
	//결정 파괴 시 가운데 네임드 + 주위 일반몹
	//비율 대충 맞춰서 해야될듯? 
	//처음 일반 3마리 잡으면 결정 -> 네임드 1마리 일반 3마리 -> 반복?
	//100% -> End
	//50~55퍼 시작 
	//네임드 3마리 15퍼 나머지 일반 30~35퍼 12마리 평균잡아서 대충 4650마리/20 232.5마리 
	//2분22.2초
	//진행도 100퍼 시 Set(End) -> HandleGameState(CurrentState);
}

void AChaosDungeonMode::EndGame()
{
	//위젯
}

void AChaosDungeonMode::Fail()
{
	//타이머 종료 소환 종료 등등
}
