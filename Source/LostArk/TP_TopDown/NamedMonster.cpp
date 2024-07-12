// Fill out your copyright notice in the Description page of Project Settings.


#include "NamedMonster.h"

ANamedMonster::ANamedMonster() : AMonster()
{
	//HP, �����
	Stat.LifePoint = Super::Stat.LifePoint * 1.5f;
	Stat.CurrentLifePoint = Stat.LifePoint;

	//���ݷ�
	Stat.ATK = Super::Stat.ATK * 1.5f;

	//����
	Stat.DEF = Super::Stat.DEF * 1.5f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//����ġ
	Stat.EXP = 0.0f;
}
