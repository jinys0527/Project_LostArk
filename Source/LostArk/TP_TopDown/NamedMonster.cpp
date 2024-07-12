// Fill out your copyright notice in the Description page of Project Settings.


#include "NamedMonster.h"

ANamedMonster::ANamedMonster() : AMonster()
{
	//HP, 생명력
	Stat.LifePoint = Super::Stat.LifePoint * 1.5f;
	Stat.CurrentLifePoint = Stat.LifePoint;

	//공격력
	Stat.ATK = Super::Stat.ATK * 1.5f;

	//방어력
	Stat.DEF = Super::Stat.DEF * 1.5f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//경험치
	Stat.EXP = 0.0f;
}
