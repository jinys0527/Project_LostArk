// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitWidget.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/ProgressWidget.h"
#include "../Widget/TimerWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "../Widget/MinimapTrixionWidget.h"
#include "../ChaosDungeon/ChaosDungeonMode.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "Kismet/GameplayStatics.h"


void UExitWidget::Exit()
{
	ATP_TopDownPlayerController* PlayerController = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());

	AChaosDungeonMode* ChaosDungeonMode = Cast<AChaosDungeonMode>(GetWorld()->GetAuthGameMode());
	if (ChaosDungeonMode)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(ChaosDungeonMode->CommonSpawnTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(ChaosDungeonMode->CommonSpawnTimer);
		}
		if (GetWorld()->GetTimerManager().IsTimerActive(ChaosDungeonMode->NamedSpawnTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(ChaosDungeonMode->NamedSpawnTimer);
		}
	}

	if (PlayerHUD)
	{	
		if (PlayerHUD->OverlayWidget)
		{
			if (PlayerHUD->OverlayWidget->WBPProgress)
			{
				PlayerHUD->OverlayWidget->WBPProgress->RemoveFromParent();
				PlayerHUD->OverlayWidget->WBPProgress = nullptr;
				PlayerHUD->OverlayWidget->WBPProgress = CreateWidget<UProgressWidget>(GetWorld(), UProgressWidget::StaticClass());
				PlayerHUD->OverlayWidget->WBPProgress->SetVisibility(ESlateVisibility::Collapsed);
			}
			if (PlayerHUD->OverlayWidget->WBPTimer)
			{
				PlayerHUD->OverlayWidget->WBPTimer->RemoveFromParent();
				PlayerHUD->OverlayWidget->WBPTimer = nullptr;
				PlayerHUD->OverlayWidget->WBPTimer = CreateWidget<UTimerWidget>(GetWorld(), UTimerWidget::StaticClass());
				PlayerHUD->OverlayWidget->WBPTimer->SetVisibility(ESlateVisibility::Collapsed);
			}
			if (PlayerHUD->OverlayWidget->WBPMiniMapLogHill)
			{
				PlayerHUD->OverlayWidget->WBPMiniMapLogHill->RemoveFromParent();
				PlayerHUD->OverlayWidget->WBPMiniMapLogHill = nullptr;
				PlayerHUD->OverlayWidget->WBPMiniMapLogHill = CreateWidget<UMinimapLogHillWidget>(GetWorld(), UMinimapLogHillWidget::StaticClass());
				PlayerHUD->OverlayWidget->WBPMiniMapLogHill->SetVisibility(ESlateVisibility::Collapsed);
			}
			if (PlayerHUD->OverlayWidget->WBPMiniMapTrixion)
			{
				PlayerHUD->OverlayWidget->WBPMiniMapTrixion->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

	UGameplayStatics::OpenLevel(GetWorld(), "L_Trixion");
}
