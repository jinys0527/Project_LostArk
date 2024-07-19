// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

APlayerHUD::APlayerHUD()
{
	
	if (Name)
	{
		Name->SetText(FText::FromString("init"));
	}
	if (CurrentHP)
	{
		CurrentHP->SetText(FText::FromString("0"));
	}
	if (MaxHP)
	{
		MaxHP->SetText(FText::FromString("0"));
	}
	if (HPBar)
	{
		HPBar->SetPercent(100.f);
	}
}

void APlayerHUD::UpdateName(FString MonsterName)
{
	Name->SetText(FText::FromString(MonsterName));
}

void APlayerHUD::UpdateCurrentHP(float MonsterCurrentHP)
{
	int32 iCurrentHP = round(MonsterCurrentHP);
	CurrentHP->SetText(FText::FromString(FString::FromInt(iCurrentHP)));
}

void APlayerHUD::SetMaxHP(float MonsterMaxHP)
{
	int32 iMonsterMaxHP = round(MonsterMaxHP);
	MaxHP->SetText(FText::FromString(FString::FromInt(iMonsterMaxHP)));
}

void APlayerHUD::UpdateHPBar(float Percent)
{
	HPBar->SetPercent(Percent);
}

float APlayerHUD::CalcPercent(float MonsterCurrentHP, float MonsterMaxHP)
{
	return MonsterCurrentHP / MonsterMaxHP;
}
