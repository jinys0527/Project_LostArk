// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "Components/TextBlock.h"

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Min)
	{
		Min->SetText(FText::FromString("05"));
	}

	if (Sec)
	{
		Sec->SetText(FText::FromString("00"));
	}
}

void UTimerWidget::UpdateTime()
{
	FString CurrentSecStr = Sec->GetText().ToString();
	FString CurrentMinStr = Min->GetText().ToString();

	if (CurrentSecStr == "00" && CurrentMinStr == "00")
	{
		bIsEnd = true;
		return;
	}

	else if (CurrentSecStr == "00" && CurrentMinStr != "00")
	{
		int32 CurrentMin = FCString::Atoi(*CurrentMinStr);
		--CurrentMin;

		FString FormattedMin = FString::Printf(TEXT("%02d"), CurrentMin);

		Min->SetText(FText::FromString(FormattedMin));
		Sec->SetText(FText::FromString(FString::FromInt(59)));
	}
	else
	{
		int32 CurrentSec = FCString::Atoi(*CurrentSecStr);
		--CurrentSec;

		FString FommattedSec = FString::Printf(TEXT("%02d"), CurrentSec);

		Sec->SetText(FText::FromString(FommattedSec));
	}

	bIsEnd = false;
}

void UTimerWidget::InitTime()
{
	Min->SetText(FText::FromString("05"));
	Sec->SetText(FText::FromString("00"));
}

void UTimerWidget::StartTimer()
{
	if (bIsEnd)
	{
		GetWorld()->GetTimerManager().ClearTimer(StageTimer);
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(StageTimer, this, &UTimerWidget::UpdateTime, 1.0f, true);
}
