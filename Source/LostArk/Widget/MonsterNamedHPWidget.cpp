// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterNamedHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMonsterNamedHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Name)
	{
		Name->SetText(FText::FromString("Named Monster"));
	}
}

float UMonsterNamedHPWidget::GetCurrentHP()
{
	float MonsterCurrentHP = FCString::Atof(*CurrentHP->GetText().ToString());
	return MonsterCurrentHP;
}

void UMonsterNamedHPWidget::SetCurrentHP(int NewCurrentHP)
{
	CurrentHP->SetText(FText::FromString(FString::FromInt(NewCurrentHP)));
}

float UMonsterNamedHPWidget::GetMaxHP()
{
	float MonsterMaxHP = FCString::Atof(*MaxHP->GetText().ToString());
	return MonsterMaxHP;
}

void UMonsterNamedHPWidget::SetMaxHP(int NewMaxHP)
{
	MaxHP->SetText(FText::FromString(FString::FromInt(NewMaxHP)));
}

void UMonsterNamedHPWidget::SetHPBarPercent(float NewCurrentHP, float NewMaxHP)
{
	HPBar->SetPercent(NewCurrentHP / NewMaxHP);
}
