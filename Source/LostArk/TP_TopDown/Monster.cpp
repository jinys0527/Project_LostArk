// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "GameFramework/Character.h"
#include "TP_TopDownPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.h"
#include "HeadMountHPWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

AMonster::AMonster() : ABaseCharacter()
{
	//HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	//HPBarWidget->SetupAttachment(RootComponent);
	//HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	////HPBarWidget->SetDrawAtDesiredSize(true);
	//HPBarWidget->SetVisibility(true);

	//HP, 생명력
	Stat.MaxLifePoint = 5000.f;
	Stat.CurrentLifePoint = Stat.MaxLifePoint;

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
	int32 RandomNumber = FMath::RandRange(1, 2);
	FString SectionName = FString::Printf(TEXT("Death_%d"), RandomNumber);
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	PlayAnimMontage(DeathMontage, 1.0f, FName(*SectionName));
	//애니메이션
}

void AMonster::PlayHitReaction()
{
	int32 RandomNumber = FMath::RandRange(1, 2);
	FString SectionName = FString::Printf(TEXT("HitReaction_%d"), RandomNumber);
	PlayAnimMontage(HitReactionMontage, 1.0f, FName(*SectionName));
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
		UE_LOG(LogTemp, Warning, TEXT("%f"), Stat.CurrentLifePoint);
	}
	else
	{
		PlayDead();
		//콜리젼 해제 + Destroy
	}

	return 0.0f;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	/*UE_LOG(LogTemp, Warning, TEXT("TEST"));
	if (HPWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("2"));
		MonsterHPBar = CreateWidget<UHPWidget>(GetWorld(), HPWidgetClass);

		if (MonsterHPBar)
		{
			UE_LOG(LogTemp, Warning, TEXT("3"));
			HPBarWidget->SetWidget(MonsterHPBar);
			UE_LOG(LogTemp, Warning, TEXT("1"));
		}
	}*/
}