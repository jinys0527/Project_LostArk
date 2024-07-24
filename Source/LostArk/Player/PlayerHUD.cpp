// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/HeadMountHPWidget.h"
#include "../Widget/MonsterBossHPWidget.h"
#include "../Widget/MonsterCommonHPWidget.h"
#include "../Widget/MonsterNamedHPWidget.h"
#include "../Widget/PlayerSlotWidget.h"
#include "../Widget/PlayerStatusWidget.h"
#include "../Widget/ProgressWidget.h"
#include "../Widget/TimerWidget.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"


APlayerHUD::APlayerHUD() : AHUD()
{
	static ConstructorHelpers::FClassFinder<UHeadMountHPWidget> HeadMountHPBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_HP_HeadMount'"));
	if (HeadMountHPBlueprint.Class)
	{
		HeadMountClass = HeadMountHPBlueprint.Class;
	}

	static ConstructorHelpers::FClassFinder<UMonsterBossHPWidget> BossHPBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_HP_Boss'"));
	if (BossHPBlueprint.Class)
	{
		BossHPClass = BossHPBlueprint.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UMonsterNamedHPWidget> NamedHPBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_HP_Named'"));
	if (NamedHPBlueprint.Class)
	{
		NamedHPClass = NamedHPBlueprint.Class;
	}

	static ConstructorHelpers::FClassFinder<UMonsterCommonHPWidget> CommonHPBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_HP_Common'"));
	if (CommonHPBlueprint.Class)
	{
		CommonHPClass = CommonHPBlueprint.Class;
	}

	static ConstructorHelpers::FClassFinder<UPlayerSlotWidget> PlayerSlotBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_PlayerSlot'"));
	if (PlayerSlotBlueprint.Class)
	{
		PlayerSlotClass = PlayerSlotBlueprint.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UPlayerStatusWidget> PlayerStatusBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_PlayerStatus'"));
	if (PlayerStatusBlueprint.Class)
	{
		PlayerStatusClass = PlayerStatusBlueprint.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UProgressWidget> ProgressBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_Progress'"));
	if (ProgressBlueprint.Class)
	{
		ProgressClass = ProgressBlueprint.Class;
	}

	static ConstructorHelpers::FClassFinder<UTimerWidget> TimerBlueprint(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_Timer'"));
	if (TimerBlueprint.Class)
	{
		TimerClass = TimerBlueprint.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerSlotClass)
	{
		PlayerSlot = CreateWidget<UPlayerSlotWidget>(PC, PlayerSlotClass);
		if (PlayerSlot)
		{
			PlayerSlot->AddToViewport();
		}
	}
	if (PlayerStatusClass)
	{
		PlayerStatus = CreateWidget<UPlayerStatusWidget>(PC, PlayerStatusClass);
		if (PlayerStatus)
		{
			PlayerStatus->AddToViewport();
		}
	}
}

void APlayerHUD::DrawHUD()
{
	
}
