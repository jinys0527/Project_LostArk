// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusBarWidget.h"
#include "Components/TextBlock.h"

FText UStatusBarWidget::GetCurrentTime() const
{
	FDateTime Now = FDateTime::Now();
	return FText::FromString(Now.ToString(TEXT("%H:%M")));
}

void UStatusBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UStatusBarWidget::UpdateTime, 1.0f, true);
}

void UStatusBarWidget::UpdateTime()
{
	CurrentTime->SetText(GetCurrentTime());
}
