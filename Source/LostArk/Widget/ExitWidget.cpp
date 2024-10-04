// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitWidget.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/ProgressWidget.h"
#include "../Widget/TimerWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "../Widget/MinimapTrixionWidget.h"
#include "../ChaosDungeon/ChaosDungeonMode.h"
#include "../LostArk/LostArkPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "../ChaosDungeon/ChaosDungeonGameInstance.h"
#include "../Player/LostArkPlayerState.h"
#include "../AbilitySystem/LostArkPlayerAttributeSet.h"
#include "../Widget/EXPBattleWidget.h"
#include "../Widget/EXPExpeditionWidget.h"
#include "../Widget/ProgressWidget.h"
#include "Components/ProgressBar.h"
#include "../Player/MyPlayer.h"
#include "Components/TextBlock.h"
#include "../AbilitySystem/LostArkAbilitySystemComponent.h"
#include "../Tag/LostArkGameplayTag.h"


void UExitWidget::Exit()
{
	ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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

	UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(PlayerController->GetPawn());
		ALostArkPlayerState* PlayerState = Cast<ALostArkPlayerState>(Player->GetPlayerState());


		if (ULostArkAbilitySystemComponent* PlayerASC = Cast<ULostArkAbilitySystemComponent>(Player->GetAbilitySystemComponent()))
		{
			if (const UAttributeSet* AttributeSet = PlayerASC->GetAttributeSet(ULostArkPlayerAttributeSet::StaticClass()))
			{
				const ULostArkPlayerAttributeSet* LostArkPlayerAttributeSet = Cast<ULostArkPlayerAttributeSet>(AttributeSet);

				if (LostArkPlayerAttributeSet)
				{
					GameInstance->PlayerBattleEXP = LostArkPlayerAttributeSet->GetEXP();
					GameInstance->PlayerExpeditionEXP = LostArkPlayerAttributeSet->GetExpeditionEXP();
					GameInstance->PlayerBattleRequiredEXP = LostArkPlayerAttributeSet->GetRequiredEXP();
					GameInstance->PlayerExpeditionRequiredEXP = LostArkPlayerAttributeSet->GetExpeditionRequiredEXP();
				}
			}
		}

		if (PlayerController)
		{
			GameInstance->PlayerBattleLevel = PlayerState->GetPlayerLevel();
			GameInstance->PlayerExpeditionLevel = PlayerState->GetPlayerExpeditionLevel();
		}

		if (PlayerHUD)
		{
			if (PlayerHUD->OverlayWidget)
			{
				if (PlayerHUD->OverlayWidget->WBPExpBattle)
				{
					GameInstance->PlayerBattleEXPBarPercent = PlayerHUD->OverlayWidget->WBPExpBattle->BattleEXPBar->GetPercent();
				}
				if (PlayerHUD->OverlayWidget->WBPExpExpedition)
				{
					GameInstance->PlayerExpeditionEXPBarPercent = PlayerHUD->OverlayWidget->WBPExpExpedition->ExpeditionEXPBar->GetPercent();
				}
			}
		}

		GetWorld()->ServerTravel("L_Trixion", true);
	}
}
