// Copyright Epic Games, Inc. All Rights Reserved.

#include "LostArkGameMode.h"
#include "LostArkPlayerController.h"
#include "../Player/MyPlayer.h"
#include "../Player/PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "../ChaosDungeon/ChaosDungeonGameInstance.h"
#include "../Widget/LoadingTrixionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/OverlayWidget.h"
#include "../Widget/MinimapLogHillWidget.h"
#include "../Widget/MinimapTrixionWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

ALostArkGameMode::ALostArkGameMode()
{
	
}

void ALostArkGameMode::BeginPlay()
{
	ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (PlayerController)
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
		Player = Cast<AMyPlayer>(PlayerController->GetPawn());

		Player->DisableInput(PlayerController);
		PlayerController->DisableInput(PlayerController);

		if (LoadingTrixionWidgetClass)
		{
			LoadingTrixionWidget = CreateWidget<ULoadingTrixionWidget>(GetWorld(), LoadingTrixionWidgetClass);
			LoadingTrixionWidget->AddToViewport();

			StartLoadingCheck();
		}

		if (PlayerHUD)
		{
			PlayerHUD->OverlayWidget->WBPMiniMapLogHill->SetVisibility(ESlateVisibility::Collapsed);
			PlayerHUD->OverlayWidget->WBPMiniMapTrixion->SetVisibility(ESlateVisibility::Visible);
		}
	}

	UChaosDungeonGameInstance* GameInstance = Cast<UChaosDungeonGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		Player = Cast<AMyPlayer>(PlayerController->GetPawn());

		Player->MaintainStatus(GameInstance);
	}

	
}

void ALostArkGameMode::Tick(float DeltaSeconds)
{
	
}

void ALostArkGameMode::StartLoadingCheck()
{
	GetWorld()->GetTimerManager().SetTimer(LoadingTimer, this, &ALostArkGameMode::CheckLoadingComplete, 0.6f, true);
}

void ALostArkGameMode::CheckLoadingComplete()
{
	if (LoadingTrixionWidget->bLoadComplete)
	{
		GetWorld()->GetTimerManager().ClearTimer(LoadingTimer);

		ALostArkPlayerController* PlayerController = Cast<ALostArkPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		if (PlayerController)
		{
			Player->EnableInput(PlayerController);
			PlayerController->EnableInput(PlayerController);
		}
	}
	else
	{
		LoadingTrixionWidget->Loopback();
	}
}
