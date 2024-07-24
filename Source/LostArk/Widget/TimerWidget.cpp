// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "Components/TextBlock.h"

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Time)
	{
		UpdateTime(300.0f);
	}
}

void UTimerWidget::UpdateTime(float NewTime)
{
	int32 iTime = round(NewTime);
	int32 Min = iTime / 60;
	int32 Sec = iTime % 60;

	FString strTime;
	strTime.Append(FString::FromInt(Min));
	strTime.Append(":");
	strTime.Append(FString::FromInt(Sec));

	Time->SetText(FText::FromString(strTime));
}