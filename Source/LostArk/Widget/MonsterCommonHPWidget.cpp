// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCommonHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

float UMonsterCommonHPWidget::GetCurrentHP()
{
	float MonsterCurrentHP = FCString::Atof(*CurrentHP->GetText().ToString());
	return MonsterCurrentHP;
}

void UMonsterCommonHPWidget::SetCurrentHP(int NewCurrentHP)
{
	CurrentHP->SetText(FText::FromString(FString::FromInt(NewCurrentHP)));
}

float UMonsterCommonHPWidget::GetMaxHP()
{
	float MonsterMaxHP = FCString::Atof(*MaxHP->GetText().ToString());
	return MonsterMaxHP;
}

void UMonsterCommonHPWidget::SetMaxHP(int NewMaxHP)
{
	MaxHP->SetText(FText::FromString(FString::FromInt(NewMaxHP)));
}

void UMonsterCommonHPWidget::SetHPBarPercent(float NewCurrentHP, float NewMaxHP)
{
	HPBar->SetPercent(NewCurrentHP / NewMaxHP);
}
