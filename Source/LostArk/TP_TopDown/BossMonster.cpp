// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"

ABossMonster::ABossMonster() : AMonster()
{
	//HP, �����
	Stat.MaxLifePoint = Super::Stat.MaxLifePoint * 2.25f;
	Stat.CurrentLifePoint = Stat.MaxLifePoint;

	//���ݷ�
	Stat.ATK = Super::Stat.ATK * 2.25f;

	//����
	Stat.DEF = Super::Stat.DEF * 2.25f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//����ġ
	Stat.EXP = 0.0f;
}
