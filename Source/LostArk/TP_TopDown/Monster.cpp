// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

AMonster::AMonster() : ABaseCharacter()
{
	//HP, �����
	Stat.LifePoint = 5000.f;
	Stat.CurrentLifePoint = Stat.LifePoint;

	//���ݷ�
	Stat.ATK = 300.f;

	//����
	Stat.DEF = 400.f;
	Stat.Block = (Stat.DEF / (Stat.DEF + 6500.f)) * 100.f;

	//����ġ
	Stat.EXP = 0.0f;
}

void AMonster::PlayDead()
{
	//�ִϸ��̼�
}

void AMonster::PlayHitReaction()
{
	//�ִϸ��̼�
}

void AMonster::Move()
{
	//�ִϸ��̼�
}

void AMonster::Attack()
{
	//�ִϸ��̼�
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
