// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCommonHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMonsterCommonHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HPBar)
	{
		HPBar->SetPercent(1.0f);
	}
	if (Name)
	{
		Name->SetText(FText::FromString(""));
	}
	if (CurrentHP)
	{
		CurrentHP->SetText(FText::FromString("0"));
	}
	if (MaxHP)
	{
		MaxHP->SetText(FText::FromString("0"));
	}
}


void UMonsterCommonHPWidget::UpdateHPBar(float CommonCurrentHP, float CommonMaxHP)
{
	float Ratio = CommonCurrentHP / CommonMaxHP;
	SetCurrentHP(FMath::Clamp(CommonCurrentHP, 0.f, CommonMaxHP));
	SetMaxHP(CommonMaxHP);
	HPBar->SetPercent(Ratio);
}

void UMonsterCommonHPWidget::UpdateName(FString NewName)
{
	Name->SetText(FText::FromString(NewName));
}

FString UMonsterCommonHPWidget::GetName()
{
	return Name->GetText().ToString();
}

float UMonsterCommonHPWidget::GetCurrentHP()
{
	return FCString::Atof(*CurrentHP->GetText().ToString());
}

float UMonsterCommonHPWidget::GetMaxHP()
{
	return FCString::Atof(*MaxHP->GetText().ToString());
}

void UMonsterCommonHPWidget::SetCurrentHP(float CommmonCurrentHP)
{
	CurrentHP->SetText(FText::FromString(FString::FromInt(round(CommmonCurrentHP))));
}

void UMonsterCommonHPWidget::SetMaxHP(float CommmonMaxHP)
{
	MaxHP->SetText(FText::FromString(FString::FromInt(round(CommmonMaxHP))));
}
