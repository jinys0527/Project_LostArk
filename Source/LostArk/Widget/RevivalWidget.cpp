// Fill out your copyright notice in the Description page of Project Settings.


#include "RevivalWidget.h"
#include "../Widget/TimerWidget.h"
#include "../Widget/OverlayWidget.h"
#include "../Player/PlayerHUD.h"
#include "../LostArk/LostArkPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void URevivalWidget::UpdateTime(int Time)
{
	ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
	if (PlayerHUD)
	{
		if (PlayerHUD->OverlayWidget)
		{
			if (PlayerHUD->OverlayWidget->WBPTimer)
			{
				Minute = Time / 60;
				Second = Time % 60;
			}
		}
	}
}
