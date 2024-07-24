// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadMountHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHeadMountHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HPBar)
	{
		HPBar->SetPercent(1.0f);
	}
}

void UHeadMountHPWidget::UpdateHPBar(float MonsterCurrentHP, float MonsterMaxHP)
{
	float Ratio = MonsterCurrentHP / MonsterMaxHP;
	HPBar->SetPercent(Ratio);
}

void UHeadMountHPWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (GetDesiredSize() != DesiredSize)
	{
		SetDesiredSizeInViewport(DesiredSize);
	}
}
