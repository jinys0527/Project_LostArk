// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapTrixionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/MinimapPlayerWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UMinimapTrixionWidget::UpdateMiniMap(UMinimapPlayerWidget* Player)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

	FVector2D PlayerMiniMapPosition = ConvertWorldToMiniMap(PlayerLocation);

	if (Player)
	{
		if (!Map->HasChild(Player))
		{
			Map->AddChild(Player);
		}

		UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Player->Slot);
		if (CanvasPanelSlot)
		{
			CanvasPanelSlot->SetPosition(PlayerMiniMapPosition);
		}
	}
}

FVector2D UMinimapTrixionWidget::ConvertWorldToMiniMap(const FVector& WorldLocation) const
{
	// 월드 좌표를 미니맵의 2D 좌표로 변환
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// 월드 좌표의 비율 계산
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);
	MiniMapPosition.Y = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);

	MiniMapPosition.X += 0.225;
	MiniMapPosition.Y = -1 * MiniMapPosition.Y + 1.075;

	// 비율을 미니맵 크기에 맞게 변환
	return MiniMapPosition * MapSize;
}