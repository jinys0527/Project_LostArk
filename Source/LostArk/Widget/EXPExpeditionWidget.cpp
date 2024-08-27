// Fill out your copyright notice in the Description page of Project Settings.


#include "EXPExpeditionWidget.h"
#include "Components/TextBlock.h"

void UEXPExpeditionWidget::UpdateBattleLevel(float NewBattleLevel)
{
	int32 NewLevel = round(NewBattleLevel);
	FString Level = FString::Printf(TEXT("%02d"), NewLevel);
	BattleLevel->SetText(FText::FromString(Level));
}

void UEXPExpeditionWidget::UpdateExpeditionLevel(float NewExpeditionLevel)
{
	int32 NewLevel = round(NewExpeditionLevel);
	FString Level = FString::Printf(TEXT("%02d"), NewLevel);
	ExpeditionLevel->SetText(FText::FromString(Level));
}
