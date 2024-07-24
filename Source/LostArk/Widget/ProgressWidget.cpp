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

void UProgressWidget::UpdateProgress(float CurrentCount, float GoalCount)
{
	float Ratio = CurrentCount / GoalCount;
	float RatioPercent = Ratio * 100.0f;
	int32 iRatioPercent = round(RatioPercent);

	ChaosDungeonProgressBar->SetPercent(Ratio);
	ProgressValue->SetText(FText::FromString(FString::FromInt(iRatioPercent)));
}
