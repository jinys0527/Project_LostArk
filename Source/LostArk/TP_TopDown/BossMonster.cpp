// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"

ABossMonster::ABossMonster() : AMonster()
{
	//HP, 생명력
	Stat.MaxLifePoint = Super::Stat.MaxLifePoint * 2.25f;
	Stat.CurrentLifePoint = Stat.MaxLifePoint;

	//공격력
	Stat.ATK = Super::Stat.ATK * 2.25f;

	//방어력
	Stat.DEF = Super::Stat.DEF * 2.25f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//경험치
	Stat.EXP = 0.0f;
}
