// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBossHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMonsterBossHPWidget::NativeConstruct()
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

void UMonsterBossHPWidget::UpdateHPBar(float BossCurrentHP, float BossMaxHP)
{
	float Ratio = BossCurrentHP / BossMaxHP;
	SetCurrentHP(FMath::Clamp(BossCurrentHP, 0.f, BossMaxHP));
	SetMaxHP(BossMaxHP);
	HPBar->SetPercent(Ratio);
}

void UMonsterBossHPWidget::UpdateName(FString NewName)
{
	Name->SetText(FText::FromString(NewName));
}

void UMonsterBossHPWidget::SetCurrentHP(float BossCurrentHP)
{
	CurrentHP->SetText(FText::FromString(FString::FromInt(round(BossCurrentHP))));
}

void UMonsterBossHPWidget::SetMaxHP(float BossMaxHP)
{
	MaxHP->SetText(FText::FromString(FString::FromInt(round(BossMaxHP))));
}

