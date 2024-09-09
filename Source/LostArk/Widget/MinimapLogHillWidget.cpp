// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapLogHillWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/MinimapPlayerWidget.h"
#include "../Widget/MinimapPortalWidget.h"
#include "../Widget/MinimapMonsterWidget.h"
#include "../Widget/MinimapNamedWidget.h"
#include "../Widget/MinimapBossWidget.h"
#include "../Monster/Monster.h"
#include "../ChaosDungeon/ChaosDungeonPortal.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UMinimapLogHillWidget::UpdatePlayer(UMinimapPlayerWidget* PlayerWidget)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

	FVector2D PlayerMiniMapPosition = ConvertWorldToMiniMap_Player(PlayerLocation);

	if (PlayerWidget)
	{
		if (!Map->HasChild(PlayerWidget))
		{
			Map->AddChild(PlayerWidget);
		}
		
		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PlayerWidget->Slot);
		if (CanvasPanelSlot)
		{
			CanvasPanelSlot->SetPosition(PlayerMiniMapPosition);
		}
	}
}

void UMinimapLogHillWidget::UpdatePortal(UMinimapPortalWidget* PortalWidget)
{
	AChaosDungeonPortal* Portal = Cast<AChaosDungeonPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), PortalClass));

	if (Portal)
	{
		FVector PortalLocation = Portal->GetActorLocation();
		FVector2D PortalMiniMapPosition = ConvertWorldToMiniMap_Portal(PortalLocation);

		if (PortalWidget)
		{
			if (!Map->HasChild(PortalWidget))
			{
				Map->AddChild(PortalWidget);

				UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PortalWidget->Slot);
				if (CanvasPanelSlot)
				{
					CanvasPanelSlot->SetPosition(PortalMiniMapPosition);
					if (!Portal->Portal->bHiddenInGame)
					{
						PortalWidget->SetVisibility(ESlateVisibility::Visible);
					}
					else
					{
						PortalWidget->SetVisibility(ESlateVisibility::Collapsed);
					}
				}
			}
			else
			{
				return;
			}
		}
	}
}

void UMinimapLogHillWidget::AddMonster(AMonster* Monster)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Monster)
	{
		switch (Monster->MonsterType)
		{
		case EMonsterType::Common:
			if (PlayerController && CommonWidgetClass)
			{
				UMinimapMonsterWidget* MinimapMonsterWidget = CreateWidget<UMinimapMonsterWidget>(PlayerController, CommonWidgetClass);

				MinimapMonsterWidget->Monster = Monster;
				Monster->MiniMapWidget = MinimapMonsterWidget;
				Monster->OnMonsterDeadWithMonster.AddDynamic(this, &UMinimapLogHillWidget::MonsterDead);
				MonsterWidget.Add(MinimapMonsterWidget);
				Map->AddChild(MonsterWidget[CommonCount]);
				MonsterLocation = MonsterWidget[CommonCount]->Monster->GetActorLocation();
				MonsterMiniMapPosition = ConvertWorldToMiniMap_Monster(MonsterLocation);
				MonsterCanvasPanelSlot = Cast<UCanvasPanelSlot>(MonsterWidget[CommonCount]->Slot);
				if (MonsterCanvasPanelSlot)
				{
					MonsterCanvasPanelSlot->SetPosition(MonsterMiniMapPosition);
				}
				CommonCount++;
			}


			break;
		case EMonsterType::Named:
			if (PlayerController && NamedWidgetClass)
			{
				UMinimapNamedWidget* MinimapNamedWidget = CreateWidget<UMinimapNamedWidget>(PlayerController, NamedWidgetClass);

				MinimapNamedWidget->Monster = Monster;
				Monster->MiniMapWidget = MinimapNamedWidget;
				Monster->OnMonsterDeadWithMonster.AddDynamic(this, &UMinimapLogHillWidget::MonsterDead);
				NamedWidget.Add(MinimapNamedWidget);
				Map->AddChild(NamedWidget[NamedCount]);
				MonsterLocation = NamedWidget[NamedCount]->Monster->GetActorLocation();
				MonsterMiniMapPosition = ConvertWorldToMiniMap_Named(MonsterLocation);
				MonsterCanvasPanelSlot = Cast<UCanvasPanelSlot>(NamedWidget[NamedCount]->Slot);
				if (MonsterCanvasPanelSlot)
				{
					MonsterCanvasPanelSlot->SetPosition(MonsterMiniMapPosition);
				}
				NamedCount++;
			}

			break;
		case EMonsterType::Boss:
			if (BossWidget)
			{
				BossWidget->Monster = Monster;
				Map->AddChild(BossWidget);
				MonsterLocation = BossWidget->Monster->GetActorLocation();
				MonsterMiniMapPosition = ConvertWorldToMiniMap_Boss(MonsterLocation);

				MonsterCanvasPanelSlot = Cast<UCanvasPanelSlot>(BossWidget->Slot);
				if (MonsterCanvasPanelSlot)
				{
					MonsterCanvasPanelSlot->SetPosition(MonsterMiniMapPosition);
				}
			}
			break;
		}
	}
}

void UMinimapLogHillWidget::UpdateMonster()
{
	TArray<UUserWidget*> MonsterWidgets = GetChildrenOfClass(Map, CommonWidgetClass);
	for (UUserWidget* CommonWidget : MonsterWidgets)
	{
		UMinimapMonsterWidget* MonsterIcon = Cast<UMinimapMonsterWidget>(CommonWidget);
		if (MonsterIcon)
		{
			if (MonsterIcon->Monster)
			{
				MonsterLocation = MonsterIcon->Monster->GetActorLocation();
				MonsterMiniMapPosition = ConvertWorldToMiniMap_Monster(MonsterLocation);

				MonsterCanvasPanelSlot = Cast<UCanvasPanelSlot>(MonsterIcon->Slot);
				if (MonsterCanvasPanelSlot)
				{
					MonsterCanvasPanelSlot->SetPosition(MonsterMiniMapPosition);
				}
			}
		}
	}

	TArray<UUserWidget*> NamedWidgets = GetChildrenOfClass(Map, NamedWidgetClass);
	for (UUserWidget* NamedMonsterWidget : NamedWidgets)
	{
		UMinimapNamedWidget* NamedIcon = Cast<UMinimapNamedWidget>(NamedMonsterWidget);
		if (NamedIcon)
		{
			if (NamedIcon->Monster)
			{
				MonsterLocation = NamedIcon->Monster->GetActorLocation();
				MonsterMiniMapPosition = ConvertWorldToMiniMap_Named(MonsterLocation);

				MonsterCanvasPanelSlot = Cast<UCanvasPanelSlot>(NamedIcon->Slot);
				if (MonsterCanvasPanelSlot)
				{
					MonsterCanvasPanelSlot->SetPosition(MonsterMiniMapPosition);
				}
			}
		}	
	}

	TArray<UUserWidget*> BossWidgets = GetChildrenOfClass(Map, BossWidgetClass);
	for (UUserWidget* BossMonsterWidget : BossWidgets)
	{
		UMinimapBossWidget* BossIcon = Cast<UMinimapBossWidget>(BossMonsterWidget);
		if (BossIcon)
		{
			if (BossIcon->Monster)
			{
				MonsterLocation = BossIcon->Monster->GetActorLocation();
				MonsterMiniMapPosition = ConvertWorldToMiniMap_Boss(MonsterLocation);

				MonsterCanvasPanelSlot = Cast<UCanvasPanelSlot>(BossIcon->Slot);
				if (MonsterCanvasPanelSlot)
				{
					MonsterCanvasPanelSlot->SetPosition(MonsterMiniMapPosition);
				}
			}
		}
	}
}

void UMinimapLogHillWidget::MonsterDead(AMonster* Monster)
{
	Monster->MiniMapWidget->RemoveFromParent();
}

TArray<UUserWidget*> UMinimapLogHillWidget::GetChildrenOfClass(UCanvasPanel* CanvasPanel, TSubclassOf<UUserWidget> WidgetClass)
{
	TArray<UUserWidget*> MatchingWidgets;
	if (!CanvasPanel) return MatchingWidgets;

	const TArray<UWidget*>& Children = CanvasPanel->GetAllChildren();

	for (UWidget* Child : Children)
	{
		if (UUserWidget* UserWidget = Cast<UUserWidget>(Child))
		{
			if (UserWidget->IsA(WidgetClass))
			{
				MatchingWidgets.Add(UserWidget);
			}
		}
	}

	return MatchingWidgets;
}

FVector2D UMinimapLogHillWidget::ConvertWorldToMiniMap_Player(const FVector& WorldLocation) const
{
	// 월드 좌표를 미니맵의 2D 좌표로 변환
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// 월드 좌표의 비율 계산
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);
	MiniMapPosition.Y = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);

	MiniMapPosition.X += 0.13;
	MiniMapPosition.Y += 0.05;

	// 비율을 미니맵 크기에 맞게 변환
	return MiniMapPosition * MapSize;
}

FVector2D UMinimapLogHillWidget::ConvertWorldToMiniMap_Portal(const FVector& WorldLocation) const
{
	// 월드 좌표를 미니맵의 2D 좌표로 변환
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// 월드 좌표의 비율 계산
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);
	MiniMapPosition.Y = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);

	MiniMapPosition.X += 0.13;
	MiniMapPosition.Y += 0.05;

	// 비율을 미니맵 크기에 맞게 변환
	return MiniMapPosition * MapSize;
}

FVector2D UMinimapLogHillWidget::ConvertWorldToMiniMap_Monster(const FVector& WorldLocation) const
{
	// 월드 좌표를 미니맵의 2D 좌표로 변환
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// 월드 좌표의 비율 계산
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);
	MiniMapPosition.Y = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);

	MiniMapPosition.X += 0.15;
	MiniMapPosition.Y += 0.05;

	// 비율을 미니맵 크기에 맞게 변환
	return MiniMapPosition * MapSize;
}

FVector2D UMinimapLogHillWidget::ConvertWorldToMiniMap_Named(const FVector& WorldLocation) const
{
	// 월드 좌표를 미니맵의 2D 좌표로 변환
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// 월드 좌표의 비율 계산
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);
	MiniMapPosition.Y = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);

	MiniMapPosition.X += 0.14;
	MiniMapPosition.Y += 0.05;

	// 비율을 미니맵 크기에 맞게 변환
	return MiniMapPosition * MapSize;
}

FVector2D UMinimapLogHillWidget::ConvertWorldToMiniMap_Boss(const FVector& WorldLocation) const
{
	// 월드 좌표를 미니맵의 2D 좌표로 변환
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// 월드 좌표의 비율 계산
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);
	MiniMapPosition.Y = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);

	MiniMapPosition.X += 0.10;
	MiniMapPosition.Y += 0.05;

	// 비율을 미니맵 크기에 맞게 변환
	return MiniMapPosition * MapSize;
}
