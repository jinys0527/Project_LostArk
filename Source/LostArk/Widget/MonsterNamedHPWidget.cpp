// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterNamedHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMonsterNamedHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Name)
	{
		Name->SetText(FText::FromString("Named Monster"));
	}
}
