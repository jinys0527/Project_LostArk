// Fill out your copyright notice in the Description page of Project Settings.


#include "NamedMonster.h"
#include "../Widget/HeadMountHPWidget.h"
#include "components/WidgetComponent.h"

ANamedMonster::ANamedMonster() : AMonster()
{
	Name = "Named Monster";

	HeadMountHPBarWidget->SetRelativeLocation(GetActorLocation() + FVector(0.f, 0.f, 120.f));

	MonsterType = EMonsterType::Named;
}

void ANamedMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ANamedMonster::PossessBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ANamedMonster::PlayDead()
{
	PlayAnimMontage(DeathMontage);
}
