// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "GameFramework/Character.h"
#include "../TP_TopDown/TP_TopDownPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "../Widget/DamageWidget.h"
#include "../Player/MyPlayer.h"
#include "../Player/PlayerHUD.h"
#include "../Widget/HeadMountHPWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "BossMonster.h"
#include "../Widget/MonsterBossHPWidget.h"
#include "../Widget/MonsterNamedHPWidget.h"
#include "../Widget/MonsterCommonHPWidget.h"
#include "NamedMonster.h"
#include "BossMonster.h"
#include "../ChaosDungeon/ChaosDungeonGameState.h"
#include "../Widget/ProgressWidget.h"

AMonster::AMonster() : ABaseCharacter()
{
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

	Name = "Common Monster";

	HeadMountHPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeadMountHPBar"));
	HeadMountHPBarWidget->SetupAttachment(RootComponent);
	HeadMountHPBarWidget->SetDrawAtDesiredSize(true);
	HeadMountHPBarWidget->SetRelativeLocation(GetActorLocation() + FVector(0.f, 0.f, 100.f));
	HeadMountHPBarWidget->SetCastShadow(false);
	HeadMountHPBarWidget->SetHiddenInGame(true);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD/WB_HP_HeadMount'"));
	if (WidgetClassFinder.Succeeded())
	{
		HeadMountHPBarWidget->SetWidgetClass(WidgetClassFinder.Class);
	}

	MonsterType = EMonsterType::Common;
}

void AMonster::PlayDead()
{
	ABaseCharacter::PlayDead();
	int32 RandomNumber = FMath::RandRange(1, 2);
	FString SectionName = FString::Printf(TEXT("Death_%d"), RandomNumber);
	UE_LOG(LogTemp, Warning, TEXT("Death"));
	PlayAnimMontage(DeathMontage, 1.0f, FName(*SectionName));
}

void AMonster::PlayHitReaction()
{
	ABaseCharacter::PlayHitReaction();
	int32 RandomNumber = FMath::RandRange(1, 2);
	FString SectionName = FString::Printf(TEXT("HitReaction_%d"), RandomNumber);
	PlayAnimMontage(HitReactionMontage, 1.0f, FName(*SectionName));
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
	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	AMyPlayer* Player = Cast<AMyPlayer>(DamageCauser);

	if (Stat.CurrentLifePoint > 0)
	{
		Stat.CurrentLifePoint -= Damage;
		if (PlayerHUD)
		{
			if (DamageClass)
			{
				wDamage = CreateWidget<UDamageWidget>(PC, DamageClass);
				if (wDamage)
				{
					wDamage->SynchronizeProperties();

					if (Player && Player->bIsCritical == true)
					{
						wDamage->DamageValue->SetColorAndOpacity(FLinearColor(0.83077, 0.617207, 0.024158));
					}
					else if (Player && Player->bIsCritical != true)
					{
						wDamage->DamageValue->SetColorAndOpacity(FLinearColor(0.871367, 0.863157, 0.863157));
					}
					wDamage->DamageValue->SetShadowOffset(FVector2D(0, 0));
					wDamage->DamageValue->SetShadowColorAndOpacity(FLinearColor::Transparent);

					FVector MonsterLocation = GetActorLocation();
					FVector PlayerLocation = DamageCauser->GetActorLocation();

					FVector DirectionVector = MonsterLocation - PlayerLocation;
					DirectionVector.Normalize();

					float DesiredDistance = 30.0f;
					WidgetLocation = MonsterLocation + (DirectionVector * DesiredDistance);

					WidgetLocation.Z = 100.0f;

					FVector2D ScreenLocation;
					UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), WidgetLocation, ScreenLocation);

					int32 RoundDamage = int32(round(Damage));
					wDamage->AddToViewport();
					wDamage->UpdateDamage(RoundDamage);
					wDamage->SetPositionInViewport(ScreenLocation, true);
				}
			}
			if (MonsterType == EMonsterType::Boss)
			{
				if (PlayerHUD->BossHP)
				{
					PlayerHUD->BossHP->UpdateHPBar(Stat.CurrentLifePoint, Stat.MaxLifePoint);
				}
			}
		}
		PlayHitReaction();
		if (Stat.CurrentLifePoint < 0)
		{
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			isAlive = false;
			PlayDead();
			FTimerHandle DeathTimer;
			GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &AMonster::Death, 1.5f, false);
			//콜리젼 해제 + Destroy
		}
	}

	if (HeadMountHPBarWidget && MonsterType != EMonsterType::Boss)
	{
		HeadMountHPBarWidget->SetHiddenInGame(false);
		UpdateHeadMountHP(Stat.CurrentLifePoint, Stat.MaxLifePoint);
	}

	return 0.0f;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster::UpdateHeadMountHP(float CurrentHP, float MaxHP)
{
	if (HeadMountHPBarWidget && HeadMountHPBarWidget->GetUserWidgetObject())
	{
		UHeadMountHPWidget* HeadMountHP = Cast<UHeadMountHPWidget>(HeadMountHPBarWidget->GetUserWidgetObject());
		if (HeadMountHP)
		{
			HeadMountHP->UpdateHPBar(CurrentHP, MaxHP);
		}
	}
}

void AMonster::Death()
{
	K2_DestroyActor();
	ATP_TopDownPlayerController* PC = Cast<ATP_TopDownPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());

	AChaosDungeonGameState* DungeonState = GetWorld()->GetGameState<AChaosDungeonGameState>();

	if (MonsterType == EMonsterType::Boss)
	{
		PlayerHUD->BossHP->SetVisibility(ESlateVisibility::Hidden);
		--DungeonState->CurrentMonsterCount;
	}
	else if (MonsterType == EMonsterType::Named)
	{
		PlayerHUD->NamedHP->SetVisibility(ESlateVisibility::Hidden);
		--DungeonState->CurrentMonsterCount;
		--DungeonState->StageNamedCount;
	}
	else
	{
		PlayerHUD->CommonHP->SetVisibility(ESlateVisibility::Hidden);
		--DungeonState->CurrentMonsterCount;
	}

	if (PlayerHUD->ProgressClass)
	{
		if (PlayerHUD->Progress)
		{
			PlayerHUD->Progress->UpdateProgress(MonsterType);
		}
	}
}