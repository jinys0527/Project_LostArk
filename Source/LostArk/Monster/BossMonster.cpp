// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"
#include "../Player/PlayerHUD.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Widget/MonsterBossHPWidget.h"
#include "../Widget/MonsterNamedHPWidget.h"
#include "../Widget/MonsterCommonHPWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

int32 ABossMonster::BossWidgetCount = 0;

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

	Name = "Boss Monster";

	bIsBoss = true;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();

	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	if (PlayerHUD)
	{
		if (PlayerHUD->BossHPClass)
		{
			if (PlayerHUD->BossHP)
			{
				if (PlayerHUD->CommonHP)
				{
					PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Hidden);
				}

				if (PlayerHUD->NamedHP)
				{
					PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Hidden);
				}

				PlayerHUD->BossHP = CreateWidget<UMonsterBossHPWidget>(PC, PlayerHUD->BossHPClass);
				if (PlayerHUD->BossHP)
				{
					PlayerHUD->BossHP->AddToViewport();
					PlayerHUD->BossHP->UpdateHPBar(Stat.CurrentLifePoint, Stat.MaxLifePoint);
					PlayerHUD->BossHP->UpdateName(Name);
				}
			}
		}

	}
}
