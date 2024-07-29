// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgressWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UProgressWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChaosDungeonProgressBar)
	{
		ChaosDungeonProgressBar->SetPercent(0.0f);
	}

	if (ProgressValue)
	{
		ProgressValue->SetText(FText::FromString("0"));
	}
}

void UProgressWidget::UpdateProgress(EMonsterType MonsterType)
{
	if (ChaosDungeonProgressBar)
	{
		float CurrentPercent = ChaosDungeonProgressBar->GetPercent();
		switch (MonsterType)
		{
		case EMonsterType::Common:
			CurrentPercent += 0.025;
			break;
		case EMonsterType::Named:
			CurrentPercent += 0.05;
			break;
		case EMonsterType::Boss:
			CurrentPercent += 0.1;
			break;
		}
		int32 iCurrentPercent = round(CurrentPercent * 100);

		ChaosDungeonProgressBar->SetPercent(CurrentPercent);
		ProgressValue->SetText(FText::FromString(FString::FromInt(iCurrentPercent)));
	}
}