// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterNamedHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMonsterNamedHPWidget::NativeConstruct()
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

void UMonsterNamedHPWidget::UpdateHPBar(float NamedCurrentHP, float NamedMaxHP)
{
	float Ratio = NamedCurrentHP / NamedMaxHP;
	SetCurrentHP(FMath::Clamp(NamedCurrentHP, 0.f, NamedMaxHP));
	SetMaxHP(NamedMaxHP);
	HPBar->SetPercent(Ratio);
}

void UMonsterNamedHPWidget::UpdateName(FString NewName)
{
	Name->SetText(FText::FromString(NewName));
}

FString UMonsterNamedHPWidget::GetName()
{
	return Name->GetText().ToString();
}

float UMonsterNamedHPWidget::GetCurrentHP()
{
	return FCString::Atof(*CurrentHP->GetText().ToString());
}

float UMonsterNamedHPWidget::GetMaxHP()
{
	return FCString::Atof(*MaxHP->GetText().ToString());
}

void UMonsterNamedHPWidget::SetCurrentHP(float NamedCurrentHP)
{
	CurrentHP->SetText(FText::FromString(FString::FromInt(round(NamedCurrentHP))));
}

void UMonsterNamedHPWidget::SetMaxHP(float NamedMaxHP)
{
	MaxHP->SetText(FText::FromString(FString::FromInt(round(NamedMaxHP))));
}
