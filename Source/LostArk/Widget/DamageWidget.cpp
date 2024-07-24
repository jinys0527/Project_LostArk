// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageWidget.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "Internationalization/Internationalization.h"

void UDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DamageValue)
	{
		DamageValue->SetText(FText::FromString("0"));
	}
}

void UDamageWidget::UpdateDamage(int32 Damage)
{
	SetDamage(Damage);
}

void UDamageWidget::SetDamage(int32 Damage)
{
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.SetUseGrouping(true); // 천 단위 구분 기호 사용
	NumberFormattingOptions.SetMinimumFractionalDigits(0); // 소수점 이하 자릿수 0

	FText DamageText = FText::AsNumber(Damage, &NumberFormattingOptions);
	DamageValue->SetText(DamageText);
}

void UDamageWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (GetDesiredSize() != DesiredSize)
	{
		SetDesiredSizeInViewport(DesiredSize);
	}
}
