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
		//��Ż ��ȯ
		return true;
	}
	return false;
}

bool AChaosDungeonMode::CheckSpawnBoss(float Percent)
{
	if (Percent >= 0.45f && Percent <= 0.5f)
	{
		//��� ���� ��ȯ
		//������ ���� ���� �����ʿ� ��Ż ��ȯ
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
	//�����ڿ��� �ϸ� Crash

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
	//�ε� ����?
	HandleGameState(CurrentState);
}

//ȯ�� �Ϲ� 25���� 2.5�� ���ӵ� 50���� 5�� ���� 100���� 10�� 
//��ǥ 1000����
//���ݸ�� 1.2�� �Ϲݸ� ������ 3��		3.6��
//���ӵ� �Ϲݸ� 1.5�� 3.6*1.5��		5.4��
//���� ���ӵ� 1.5�� 3.6*1.5*1.5��		8.1��
//Ÿ�̸� ������ 15�� ����, Ÿ�ӿ����� Fail��
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

	//���� �Ϲݸ� ��ȯ �ִ� ������ ª�� �� �ð� ����
	//18~20% ��Ż ��ȯ(�Ķ���)
	//�Ϲ� 8���� 1�� 12��
	//��Ż �̵��� ��Ż ��ȣ�ۿ� �� Set(Stage2) -> Handle
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



	//���� �Ϲݸ� + ���ӵ� ��ȯ(�ִ� 2����, ������)
	//45~50% ���� ��ȯ(���൵)
	//���� ������ ��Ż��ȯ(������)
	//���ӵ� ���� 4���� 20�� �Ϲ� 10�� 4����, �Ϲ��� ���� ��� ��ȯ
	//���� 10�� 100���� 
	//1�� 5.7��
	//��Ż �̵��� Set(Stage3) -> Handle
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
	//���� �Ϲݸ� + ���ӵ� ��ȯ - �������� �� �� 
	//�����ʸ� �̵���Ű�� �Ϲݸ� �� ������ ���� ��ȯ 
	//���� �ı� �� ��� ���ӵ� + ���� �Ϲݸ�
	//���� ���� ���缭 �ؾߵɵ�? 
	//ó�� �Ϲ� 3���� ������ ���� -> ���ӵ� 1���� �Ϲ� 3���� -> �ݺ�?
	//100% -> End
	//50~55�� ���� 
	//���ӵ� 3���� 15�� ������ �Ϲ� 30~35�� 12���� �����Ƽ� ���� 4650����/20 232.5���� 
	//2��22.2��
	//���൵ 100�� �� Set(End) -> HandleGameState(CurrentState);
}

void AChaosDungeonMode::EndGame()
{
	//����
}

void AChaosDungeonMode::Fail()
{
	//Ÿ�̸� ���� ��ȯ ���� ���
}
