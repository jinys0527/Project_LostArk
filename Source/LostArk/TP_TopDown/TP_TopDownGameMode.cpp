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
	//로딩 위젯?
}

//환산 일반 10마리 1퍼 네임드 50마리 5퍼 보스 100마리 10퍼 
//목표 1000마리
//공격모션 1.2초 일반몹 마리당 3대		3.6초
//네임드 일반몹 1.5배 3.6*1.5초		5.4초
//보스 네임드 1.5배 3.6*1.5*1.5초		8.1초
void ATP_TopDownGameMode::StartGame()
{
	//카오스 던전 출력
	//레벨이동, 타이머, 진행도 띄우기
	//->Stage1
}

void ATP_TopDownGameMode::StartStage1()
{
	//랜덤 일반몹 소환
	//18~20% 포탈 소환(파란색)
	//일반 20마리 1분 12초
}

void ATP_TopDownGameMode::StartStage2()
{
	//랜덤 일반몹 + 네임드 소환
	//45~50% 보스 소환
	//보스 잡으면 포탈소환(검은색)
	//네임드 대충 4마리 20퍼 일반 10퍼 10마리, 일반은 대충 계속 소환
	//보스 10퍼 100마리 
	//1분 5.7초
}

void ATP_TopDownGameMode::StartStage3()
{
	//랜덤 일반몹 + 네임드 소환
	//100% -> End
	//50~55퍼 시작 
	//네임드 3마리 15퍼 나머지 일반 30~35퍼 30~35마리 평균잡아서 대충 4650마리/20 232.5마리 
	//2분22.2초
}
//총 소요시간 4분40초?
void ATP_TopDownGameMode::EndGame()
{
	//위젯
}
