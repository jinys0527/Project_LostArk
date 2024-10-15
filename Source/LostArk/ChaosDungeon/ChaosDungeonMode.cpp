// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonMode.h"
#include "Kismet/GameplayStatics.h"
#include "../LostArk/LostArkPlayerController.h"
#include "MonsterSpawner.h"
#include "../Player/MyPlayer.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/TimerWidget.h"
#include "../Widget/ProgressWidget.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "../Widget/MinimapTrixionWidget.h"
#include "../Monster/BossMonster.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosDungeonPortal.h"
#include "BossMonsterSpawner.h"
#include "Blueprint/UserWidget.h"
#include "ChaosDungeonGameInstance.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"
#include "../Player/LostArkPlayerState.h"
#include "../Tag/LostArkGameplayTag.h"
#include "../Widget/LoadingLogHillWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

AChaosDungeonMode::AChaosDungeonMode()
{
	SetCurrentState(EDungeonState::None);
	bUseSeamlessTravel = true;
}

void AChaosDungeonMode::OnProgressChanged(float NewProgress)
{
	if (NewProgress >= 0.18f && NewProgress <= 0.19f)
	{
		AChaosDungeonPortal* Portal = Cast<AChaosDungeonPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), PortalClass));
		if (Portal)
		{
			Portal->SetVisiblePortal();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Null Portal"));
		}
	}

	if (NewProgress >= 0.45f && NewProgress <= 0.5f)
	{
		BossPortal = Cast<AChaosDungeonPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), PortalClass));
		Location = BossPortal->GetActorLocation();
		Location.Z = 275.f;
		Rotation = BossPortal->GetActorRotation();
		ABossMonsterSpawner* Spawner = GetWorld()->SpawnActor<ABossMonsterSpawner>(BossMonsterSpawnerClass, Location, Rotation);
		ABossMonster* Boss = Spawner->SpawnBossMonster(Location, Rotation);
		if (Boss)
		{
			Boss->OnMonsterDead.AddDynamic(this, &AChaosDungeonMode::OnBossDead);
		}

		if (PlayerHUD && PlayerHUD->OverlayWidget && PlayerHUD->OverlayWidget->WBPProgress)
		{
			PlayerHUD->OverlayWidget->WBPProgress->BindToMonster(Boss);
		}
	}

	if (NewProgress == 1.0f)
	{
		SetCurrentState(EDungeonState::End);
	}
}

void AChaosDungeonMode::OnBossDead()
{
	BossPortal->SetVisiblePortal();
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

void AChaosDungeonMode::SetCurrentState(EDungeonState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;

	OnDungeonStateChanged.Broadcast(NewState);

	CurrentDungeonState->SetCurrentState(NewState);
}

void AChaosDungeonMode::BeginPlay()
{
	CurrentDungeonState = GetWorld()->GetGameState<AChaosDungeonGameState>();
	PC = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	if (PC)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(PC->GetPawn());
		Player->DisableInput(PC);
		PC->DisableInput(PC);

		if (PlayerHUD)
		{
			if (PlayerHUD->OverlayWidget)
			{
				if (PlayerHUD->OverlayWidget->WBPMiniMapTrixion)
				{
					PlayerHUD->OverlayWidget->WBPMiniMapTrixion->SetVisibility(ESlateVisibility::Collapsed);
				}
				if (PlayerHUD->OverlayWidget->WBPMiniMapLogHill)
				{
					PlayerHUD->OverlayWidget->WBPMiniMapLogHill->SetVisibility(ESlateVisibility::Visible);
				}

				OnDungeonStateChanged.AddDynamic(this, &AChaosDungeonMode::HandleGameState);

				if (PlayerHUD->OverlayWidget->WBPProgress)
				{
					PlayerHUD->OverlayWidget->WBPProgress->SetVisibility(ESlateVisibility::Visible);
					PlayerHUD->OverlayWidget->WBPProgress->OnProgressBarChanged.AddDynamic(this, &AChaosDungeonMode::OnProgressChanged);
				}

				if (PlayerHUD->OverlayWidget->WBPTimer)
				{
					PlayerHUD->OverlayWidget->WBPTimer->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}

		FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		if (LevelName == "L_LogHill_Stage1")
		{
			if (LoadingLogHillWidgetClass[0])
			{
				LoadingLogHillWidget = CreateWidget<ULoadingLogHillWidget>(GetWorld(), LoadingLogHillWidgetClass[0]);
				LoadingLogHillWidget->AddToViewport();

				StartLoadingCheck();
			}
		}
		else if (LevelName == "L_LogHill_Stage2")
		{
			if (LoadingLogHillWidgetClass[1])
			{
				LoadingLogHillWidget = CreateWidget<ULoadingLogHillWidget>(GetWorld(), LoadingLogHillWidgetClass[1]);
				LoadingLogHillWidget->AddToViewport();

				StartLoadingCheck();
			}
		}
		else if (LevelName == "L_LogHill_Stage3")
		{
			if (LoadingLogHillWidgetClass[2])
			{
				LoadingLogHillWidget = CreateWidget<ULoadingLogHillWidget>(GetWorld(), LoadingLogHillWidgetClass[2]);
				LoadingLogHillWidget->AddToViewport();

				StartLoadingCheck();
			}
		}
	}

	UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(PC->GetPawn());

		Player->MaintainStatus(GameInstance);
	}
}

void AChaosDungeonMode::Tick(float DeltaSeconds)
{
}

void AChaosDungeonMode::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(StageTimer, this, &AChaosDungeonMode::UpdateTime, 1.0f, true);
}

void AChaosDungeonMode::UpdateTime()
{
	Time -= 1;
	Time = FMath::Max(Time, 0);
}

void AChaosDungeonMode::DeathPenalty()
{
	Time -= 15;
	Time = FMath::Max(Time, 0);
}

void AChaosDungeonMode::HandleGameState(EDungeonState NewState)
{
	switch (NewState)
	{
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

//ȯ�� �Ϲ� 25���� 2.5�� ���ӵ� 50���� 5�� ���� 100���� 10�� 
//��ǥ 1000����
//���ݸ�� 1.2�� �Ϲݸ� ������ 3��		3.6��
//���ӵ� �Ϲݸ� 1.5�� 3.6*1.5��		5.4��
//���� ���ӵ� 1.5�� 3.6*1.5*1.5��		8.1��
//Ÿ�̸� ������ 15�� ����, Ÿ�ӿ����� Fail��
void AChaosDungeonMode::StartGame()
{
	if (PlayerHUD->OverlayWidget->WBPTimer)
	{
		PlayerHUD->OverlayWidget->WBPTimer->SetVisibility(ESlateVisibility::Visible);
	}

	if (PlayerHUD->OverlayWidget->WBPProgress)
	{
		PlayerHUD->OverlayWidget->WBPProgress->SetVisibility(ESlateVisibility::Visible);
	}
	SetCurrentState(EDungeonState::Stage1);
}

void AChaosDungeonMode::StartStage1()
{
	Time = 300;
	StartTimer();
	if (PlayerHUD)
	{
		if (PlayerHUD->OverlayWidget->WBPTimer)
		{
			if (Time == 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(StageTimer);
				SetCurrentState(EDungeonState::Fail);
			}

			PlayerHUD->OverlayWidget->WBPTimer->InitTime(Time);
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
		0.75f,
		true);

	//���� �Ϲݸ� ��ȯ �ִ� ������ ª�� �� �ð� ����
	//18~20% ��Ż ��ȯ(�Ķ���)
	//�Ϲ� 8���� 1�� 12��
	//��Ż �̵��� ��Ż ��ȣ�ۿ� �� Set(Stage2) -> Handle
}

void AChaosDungeonMode::StartStage2()
{
	Time = 300;
	StartTimer();
	if (PlayerHUD)
	{
		if (PlayerHUD->OverlayWidget->WBPTimer)
		{
			if (Time == 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(StageTimer);
				SetCurrentState(EDungeonState::Fail);
			}

			PlayerHUD->OverlayWidget->WBPTimer->InitTime(Time);
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
		0.75f,
		true);

	GetWorld()->GetTimerManager().SetTimer(
		NamedSpawnTimer,
		[this]()
		{
			SpawnMonsterAtRandom(EMonsterType::Named);
		},
		1.0f,
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
	Time = 300;
	StartTimer();
	if (PlayerHUD)
	{
		if (PlayerHUD->OverlayWidget->WBPTimer)
		{
			if (Time == 0)
			{
				GetWorld()->GetTimerManager().ClearTimer(StageTimer);
				SetCurrentState(EDungeonState::Fail);
			}

			PlayerHUD->OverlayWidget->WBPTimer->InitTime(Time);
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
	if (CompleteClass)
	{
		UUserWidget* CompleteWidget = CreateWidget<UUserWidget>(GetWorld(), CompleteClass);
		if (CompleteWidget)
		{
			CompleteWidget->AddToViewport();
		}
	}
}

void AChaosDungeonMode::Fail()
{
	GetWorld()->GetTimerManager().ClearTimer(CommonSpawnTimer);
	GetWorld()->GetTimerManager().ClearTimer(NamedSpawnTimer);
	TArray<AActor*> Monsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), MonsterClass, Monsters);

	for (AActor* Monster : Monsters)
	{
		AMonster* CurrentMonster = Cast<AMonster>(Monster);
		CurrentMonster->Destroy();
	}
}

void AChaosDungeonMode::StartLoadingCheck()
{
	GetWorld()->GetTimerManager().SetTimer(LoadingTimer, this, &AChaosDungeonMode::CheckLoadingComplete, 0.6f, true);
}

void AChaosDungeonMode::CheckLoadingComplete()
{
	if (LoadingLogHillWidget->bLoadComplete)
	{
		GetWorld()->GetTimerManager().ClearTimer(LoadingTimer);

		AMyPlayer* Player = Cast<AMyPlayer>(PC->GetPawn());
		Player->EnableInput(PC);
		PC->EnableInput(PC);

		FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		if (LevelName == "L_LogHill_Stage1")
		{
			SetCurrentState(EDungeonState::Stage1);
			Player = Cast<AMyPlayer>(PC->GetPawn());
			float EffectLevel = Player->GetPlayerLevel();
			Player->ApplyEffectToSelf(Player->InitEXPEffectClass, EffectLevel + 1);
		}
		else if (LevelName == "L_LogHill_Stage2")
		{
			SetCurrentState(EDungeonState::Stage2);
		}
		else if (LevelName == "L_LogHill_Stage3")
		{
			SetCurrentState(EDungeonState::Stage3);
		}
	}
	else
	{
		LoadingLogHillWidget->Loopback();
	}
}
