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
#include "../Widget/EXPExpeditionWidget.h"
#include "../Widget/MinimapLogHillWidget.h"


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
	if (OverlayWidget->WBPExpExpedition)
	{
		OverlayWidget->WBPExpExpedition->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OverlayWidget->WBPMiniMapLogHill)
	{
		OverlayWidget->WBPMiniMapLogHill->SetVisibility(ESlateVisibility::Collapsed);
	}
	Widget->AddToViewport();
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
}
