// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapTrixionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/MinimapPlayerWidget.h"
#include "../Widget/MinimapPortalWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UMinimapTrixionWidget::UpdatePlayer(UMinimapPlayerWidget* PlayerWidget)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		if (PlayerController->GetPawn())
		{
			FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

			FVector2D PlayerMiniMapPosition = ConvertWorldToMiniMap(PlayerLocation);

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
	}
}

void UMinimapTrixionWidget::UpdatePortal(UMinimapPortalWidget* PortalWidget)
{
	AActor* Portal = UGameplayStatics::GetActorOfClass(GetWorld(), Portalclass);

	if (Portal)
	{
		FVector PortalLocation = Portal->GetActorLocation();
		FVector2D PortalMiniMapPosition = ConvertWorldToMiniMap(PortalLocation);

		if (!Map->HasChild(PortalWidget))
		{
			Map->AddChild(PortalWidget);

			UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(PortalWidget->Slot);
			if (CanvasPanelSlot)
			{
				CanvasPanelSlot->SetPosition(PortalMiniMapPosition);
			}
		}
		else
		{
			return;
		}
	}
}

FVector2D UMinimapTrixionWidget::ConvertWorldToMiniMap(const FVector& WorldLocation) const
{
	// ���� ��ǥ�� �̴ϸ��� 2D ��ǥ�� ��ȯ
	FVector2D World2D(WorldLocation.X, WorldLocation.Y);

	FVector2D MapSize = MiniMapSize;

	// ���� ��ǥ�� ���� ���
	FVector2D MiniMapPosition;
	MiniMapPosition.X = (World2D.Y - WorldBoundsMin.Y) / (WorldBoundsMax.Y - WorldBoundsMin.Y);
	MiniMapPosition.Y = (World2D.X - WorldBoundsMin.X) / (WorldBoundsMax.X - WorldBoundsMin.X);

	MiniMapPosition.X += 0.225;
	MiniMapPosition.Y = -1 * MiniMapPosition.Y + 1.075;

	// ������ �̴ϸ� ũ�⿡ �°� ��ȯ
	return MiniMapPosition * MapSize;
}