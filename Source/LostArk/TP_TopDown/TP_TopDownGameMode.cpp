// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_TopDownGameMode.h"
#include "TP_TopDownPlayerController.h"
#include "../Player/MyPlayer.h"
#include "UObject/ConstructorHelpers.h"
#include "ChaosDungeonGameState.h"

ATP_TopDownGameMode::ATP_TopDownGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATP_TopDownPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	CurrentState = EChaosDungeonGameState::PreStart;
}

void ATP_TopDownGameMode::SetCurrentState(EChaosDungeonGameState NewState)
{
	if (CurrentState == NewState)
	{
		return;
	}

	CurrentState = NewState;
	HandleGameState(NewState);


	AGameModeBase* LostArkState = GetGameState<AGameModeBase>();
	if (LostArkState)
	{
		AChaosDungeonGameState* ChaosDungeonState = Cast<AChaosDungeonGameState>(LostArkState);
		ChaosDungeonState->SetCurrentState(NewState);
	}
}

void ATP_TopDownGameMode::BeginPlay()
{
}

void ATP_TopDownGameMode::Tick(float DeltaSeconds)
{
}

void ATP_TopDownGameMode::HandleGameState(EChaosDungeonGameState NewState)
{
	switch (NewState)
	{
	case EChaosDungeonGameState::PreStart:
		Loading();
		break;
	case EChaosDungeonGameState::Start:
		StartGame();
		break;
	case EChaosDungeonGameState::Stage1:
		StartStage1();
		break;
	case EChaosDungeonGameState::Stage2:
		StartStage2();
		break;
	case EChaosDungeonGameState::Stage3:
		StartStage3();
		break;
	case EChaosDungeonGameState::End:
		EndGame();
		break;
	}
}

void ATP_TopDownGameMode::Loading()
{
	//�ε� ����?
}

//ȯ�� �Ϲ� 10���� 1�� ���ӵ� 50���� 5�� ���� 100���� 10�� 
//��ǥ 1000����
//���ݸ�� 1.2�� �Ϲݸ� ������ 3��		3.6��
//���ӵ� �Ϲݸ� 1.5�� 3.6*1.5��		5.4��
//���� ���ӵ� 1.5�� 3.6*1.5*1.5��		8.1��
void ATP_TopDownGameMode::StartGame()
{
	//ī���� ���� ���
	//�����̵�, Ÿ�̸�, ���൵ ����
	//->Stage1
}

void ATP_TopDownGameMode::StartStage1()
{
	//���� �Ϲݸ� ��ȯ
	//18~20% ��Ż ��ȯ(�Ķ���)
	//�Ϲ� 20���� 1�� 12��
}

void ATP_TopDownGameMode::StartStage2()
{
	//���� �Ϲݸ� + ���ӵ� ��ȯ
	//45~50% ���� ��ȯ
	//���� ������ ��Ż��ȯ(������)
	//���ӵ� ���� 4���� 20�� �Ϲ� 10�� 10����, �Ϲ��� ���� ��� ��ȯ
	//���� 10�� 100���� 
	//1�� 5.7��
}

void ATP_TopDownGameMode::StartStage3()
{
	//���� �Ϲݸ� + ���ӵ� ��ȯ
	//100% -> End
	//50~55�� ���� 
	//���ӵ� 3���� 15�� ������ �Ϲ� 30~35�� 30~35���� �����Ƽ� ���� 4650����/20 232.5���� 
	//2��22.2��
}
//�� �ҿ�ð� 4��40��?
void ATP_TopDownGameMode::EndGame()
{
	//����
}
