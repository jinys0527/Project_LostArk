// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"
#include "../Player/PlayerHUD.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "../Widget/MonsterBossHPWidget.h"
#include "../Widget/MonsterNamedHPWidget.h"
#include "../Widget/MonsterCommonHPWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../Widget/OverlayWidget.h"
#include "Components/WidgetComponent.h"
#include "../Animation/AnimInstance_Monster.h"

int32 ABossMonster::BossWidgetCount = 0;

ABossMonster::ABossMonster() : AMonster()
{
	AnimInstance = Cast<UAnimInstance_Monster>(GetMesh()->GetAnimInstance());

	Name = "Boss Monster";

	MonsterType = EMonsterType::Boss;
}

void ABossMonster::SetDead()
{
	Super::SetDead();
}

void ABossMonster::PlayFire()
{
	PlayAnimMontage(FireMontage, 1.0f);
}

void ABossMonster::PlayHitReaction()
{
	if (AnimInstance)
	{
		if (!AnimInstance->Montage_IsPlaying(AttackMontage) && !AnimInstance->Montage_IsPlaying(FireMontage))
		{
			PlayAnimMontage(HitReactionMontage, 1.0f);
		}
	}
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();

	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	if (PlayerHUD)
	{
		if (PlayerHUD->CommonHP)
		{
			PlayerHUD->OverlayWidget->WBPHPCommon->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (PlayerHUD->NamedHP)
		{
			PlayerHUD->OverlayWidget->WBPHPNamed->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (PlayerHUD->BossHP)
		{
			PlayerHUD->OverlayWidget->WBPHPBoss->SetVisibility(ESlateVisibility::Visible);
		}

	}
}

void ABossMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}
