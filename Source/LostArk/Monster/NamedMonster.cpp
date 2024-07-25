// Fill out your copyright notice in the Description page of Project Settings.


#include "NamedMonster.h"
#include "../Widget/HeadMountHPWidget.h"
#include "components/WidgetComponent.h"

ANamedMonster::ANamedMonster() : AMonster()
{
	//HP, �����
	Stat.MaxLifePoint = Super::Stat.MaxLifePoint * 1.5f;
	Stat.CurrentLifePoint = Stat.MaxLifePoint;

	//���ݷ�
	Stat.ATK = Super::Stat.ATK * 1.5f;

	//����
	Stat.DEF = Super::Stat.DEF * 1.5f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//����ġ
	Stat.EXP = 0.0f;

	Name = "Named Monster";

	HeadMountHPBarWidget->SetRelativeLocation(GetActorLocation() + FVector(0.f, 0.f, 120.f));

	MonsterType = EMonsterType::Named;
}
