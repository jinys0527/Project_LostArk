// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingTrixionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"

ULoadingTrixionWidget::ULoadingTrixionWidget() : ULoadingWidget()
{
}

void ULoadingTrixionWidget::Loading()
{
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "Loopback";
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;
	UGameplayStatics::LoadStreamLevel(GetWorld(), SubLevelName[LevelIndex], true, false, LatentInfo);
	LevelIndex++;
}

void ULoadingTrixionWidget::Loopback()
{
	if (LevelIndex < SubLevelName.Num())
	{
		LoadingGauge->SetPercent(static_cast<float>(LevelIndex) / static_cast<float>(SubLevelName.Num()));
		LoadingGaugeArrow->SetValue(static_cast<float>(LevelIndex) / static_cast<float>(SubLevelName.Num()));
		Loading();
	}
	else if (LevelIndex == SubLevelName.Num())
	{
		LoadingGauge->SetPercent(static_cast<float>(LevelIndex) / static_cast<float>(SubLevelName.Num()));
		LoadingGaugeArrow->SetValue(static_cast<float>(LevelIndex) / static_cast<float>(SubLevelName.Num()));
		bLoadComplete = true;
		RemoveFromParent();
	}
}
