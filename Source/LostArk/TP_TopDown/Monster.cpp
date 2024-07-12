// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

AMonster::AMonster() : ABaseCharacter()
{
	//HP, 생명력
	Stat.LifePoint = 5000.f;
	Stat.CurrentLifePoint = Stat.LifePoint;

	//공격력
	Stat.ATK = 300.f;

	//방어력
	Stat.DEF = 400.f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//경험치
	Stat.EXP = 0.0f;
}

void AMonster::PlayDead()
{
	//애니메이션
}

void AMonster::PlayHitReaction()
{
	//애니메이션
}

void AMonster::Move()
{
	//애니메이션
}

void AMonster::Attack()
{
	//애니메이션
}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (Stat.CurrentLifePoint > 0)
	{
		PlayHitReaction();
		Stat.CurrentLifePoint -= Damage;

	}
	else
	{
		PlayDead();
	}

	return 0.0f;
}
