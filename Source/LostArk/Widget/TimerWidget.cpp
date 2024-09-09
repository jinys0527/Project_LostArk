// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "Components/TextBlock.h"


void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTimerWidget::UpdateTime(int Time)
{
	int Minute = Time / 60;
	int Second = Time % 60;

	if (Minute == 0 && Second == 0)
	{
		return;
	}

	Min->SetText(FText::FromString(FString::Printf(TEXT("%02d"), Minute)));
	Sec->SetText(FText::FromString(FString::Printf(TEXT("%02d"), Second)));
}

void UTimerWidget::InitTime(int Time)
{
	int Minute = Time / 60;
	int Second = Time % 60;
	Min->SetText(FText::FromString(FString::Printf(TEXT("%02d"), Minute)));
	Sec->SetText(FText::FromString(FString::Printf(TEXT("%02d"), Second)));
}