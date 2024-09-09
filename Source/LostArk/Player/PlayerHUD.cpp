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
#include "../Widget/OverlayWidget.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Widget/OverlayWidgetController.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "../Widget/MinimapTrixionWidget.h"
#include "../Widget/RevivalWidget.h"
#include "../Player/LostArkPlayerState.h"
#include "../Widget/EnterWidget.h"
#include "../Widget/LevelUpWidget.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Animation/WidgetAnimation.h"


APlayerHUD::APlayerHUD() : AHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}

UOverlayWidgetController* APlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void APlayerHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class Uninitialized, please fill out BP_PlayerHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class Uninitialized, please fill out BP_PlayerHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UOverlayWidget>(Widget);
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	ALostArkPlayerState* LostArkPlayerState = Cast<ALostArkPlayerState>(PS);
	if (OverlayWidget->WBPHPBoss)
	{
		OverlayWidget->WBPHPBoss->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPHPNamed)
	{
		OverlayWidget->WBPHPNamed->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPHPCommon)
	{
		OverlayWidget->WBPHPCommon->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPTimer)
	{
		OverlayWidget->WBPTimer->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPProgress)
	{
		OverlayWidget->WBPProgress->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPExpBattle)
	{
		OverlayWidget->WBPExpBattle->UpdateBattleLevel(LostArkPlayerState->GetPlayerLevel());
		OverlayWidget->WBPExpBattle->UpdateExpeditionLevel(LostArkPlayerState->GetPlayerExpeditionLevel());
	}
	if (OverlayWidget->WBPExpExpedition)
	{
		OverlayWidget->WBPExpExpedition->UpdateBattleLevel(LostArkPlayerState->GetPlayerLevel());
		OverlayWidget->WBPExpExpedition->UpdateExpeditionLevel(LostArkPlayerState->GetPlayerExpeditionLevel());
		OverlayWidget->WBPExpExpedition->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPMiniMapLogHill && OverlayWidget->WBPMiniMapTrixion)
	{
		FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		if (LevelName == "L_Trixion")
		{
			OverlayWidget->WBPMiniMapLogHill->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			OverlayWidget->WBPMiniMapTrixion->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (OverlayWidget->WBPRevival)
	{
		OverlayWidget->WBPRevival->SetVisibility(ESlateVisibility::Hidden);
	}
	if (OverlayWidget->WBPEnter)
	{
		OverlayWidget->WBPEnter->SetVisibility(ESlateVisibility::Collapsed);
	}
	Widget->AddToViewport();
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
}

void APlayerHUD::SpawnLevelUPWidgetWithAnimation(FVector Location)
{
	if (LevelUPWidgetClass)
	{
		// 위젯을 생성
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LevelUPWidgetClass);
		LevelUPWidget = Cast<ULevelUpWidget>(Widget);
		if (LevelUPWidget)
		{
			// 위젯을 뷰포트에 추가
			LevelUPWidget->AddToViewport();

			// 애니메이션을 재생 (위젯 내에서 애니메이션을 찾아야 함)
			UWidgetAnimation* Animation = LevelUPWidget->LevelUp; // 애니메이션 이름을 넣음
			if (Animation)
			{
				// 애니메이션을 재생
				Widget->PlayAnimation(Animation);

				// 애니메이션이 끝난 후 위젯을 삭제하기 위한 타이머 설정
				float AnimationLength = Animation->GetEndTime();
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &APlayerHUD::RemoveWidget, Widget), AnimationLength, false);
			}
		}
	}
}

void APlayerHUD::RemoveWidget(UUserWidget* Widget)
{
	if (Widget)
	{
		Widget->RemoveFromParent();
		Widget->Destruct();
	}
}
