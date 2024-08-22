// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatusWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*if (HPBar)
	{
		HPBar->SetPercent(1.0f);
	}
	if (MPBar)
	{
		MPBar->SetPercent(1.0f);
	}
	if (CurrentHP)
	{
		CurrentHP->SetText(FText::FromString("0"));
	}
	if (MaxHP)
	{
		MaxHP->SetText(FText::FromString("0"));
	}
	if (CurrentMP)
	{
		CurrentMP->SetText(FText::FromString("0"));
	}
	if (MaxMP)
	{
		MaxMP->SetText(FText::FromString("0"));
	}*/
}

void UPlayerStatusWidget::UpdateHPBar(float PlayerCurrentHP, float PlayerMaxHP)
{
	float Ratio = PlayerCurrentHP / PlayerMaxHP;
	SetCurrentHP(FMath::Clamp(PlayerCurrentHP, 0.f, PlayerMaxHP));
	//SetMaxHP(PlayerMaxHP);
	HPBar->SetPercent(Ratio);
}

void UPlayerStatusWidget::UpdateMPBar(float PlayerCurrentMP, float PlayerMaxMP)
{
	float Ratio = PlayerCurrentMP / PlayerMaxMP;
	SetCurrentMP(FMath::Clamp(PlayerCurrentMP, 0.f, PlayerMaxMP));
	SetMaxMP(PlayerMaxMP);
	MPBar->SetPercent(Ratio);
}

void UPlayerStatusWidget::SetCurrentHP(float PlayerCurrentHP)
{
	//CurrentHP->SetText(FText::FromString(FString::FromInt(round(PlayerCurrentHP))));
}

void UPlayerStatusWidget::SetMaxHP(float PlayerMaxHP)
{
	MaxHP->SetText(FText::FromString(FString::FromInt(round(PlayerMaxHP))));
}

void UPlayerStatusWidget::SetCurrentMP(float PlayerCurrentMP)
{
	CurrentMP->SetText(FText::FromString(FString::FromInt(round(PlayerCurrentMP))));
}

void UPlayerStatusWidget::SetMaxMP(float PlayerMaxMP)
{
	MaxMP->SetText(FText::FromString(FString::FromInt(round(PlayerMaxMP))));
}

float UPlayerStatusWidget::GetCurrentHP()
{
	return FCString::Atof(*CurrentHP->GetText().ToString());
}

float UPlayerStatusWidget::GetMaxHP()
{
	return FCString::Atof(*MaxHP->GetText().ToString());
}

float UPlayerStatusWidget::GetCurrentMP()
{
	return FCString::Atof(*CurrentMP->GetText().ToString());
}

float UPlayerStatusWidget::GetMaxMP()
{
	return FCString::Atof(*MaxMP->GetText().ToString());
}
