// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadMountHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHeadMountHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HPBar)
	{
		HPBar->SetPercent(100.0f);
	}
}

void UHeadMountHPWidget::UpdateHPBar(float Percent)
{
	HPBar->SetPercent(Percent);
}

float UHeadMountHPWidget::CalcPercent(float MonsterCurrentHP, float MonsterMaxHP)
{
	return MonsterCurrentHP / MonsterMaxHP;
}
