// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBossHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMonsterBossHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Name)
	{
		Name->SetText(FText::FromString("Boss Monster"));
	}
}
